#include "TodoList.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdexcept>
#include <windows.h>

void enableANSIColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

void create_list(const std::string& name, const Date& date, const std::vector<std::string>& tasks) {
    std::ofstream index("index.txt", std::ios::app);
    index << name << "\n";
    index.close();

    TodoList list(name);
    list.date = date;
    for (const auto& task : tasks) {
        list.add_task(task);
    }

    std::cout << "\033[1;32mList \"" << name << "\" created successfully.\033[0m\n";
}

void delete_list(const std::string& name) {
    if (!std::filesystem::exists("lists/" + name + ".txt")) {
        std::cerr << "\033[1;31mList \"" << name << "\" does not exist.\033[0m\n";
        return;
    }

    std::ifstream in("index.txt");
    std::ofstream temp("temp.txt");
    std::string line;

    while (std::getline(in, line)) {
        if (line != name) temp << line << "\n";
    }
    in.close();
    temp.close();

    std::filesystem::remove("index.txt");
    std::filesystem::rename("temp.txt", "index.txt");
    std::filesystem::remove("lists/" + name + ".txt");

    std::cout << "\033[1;33mList \"" << name << "\" deleted.\033[0m\n";
}

void view_lists() {
    std::ifstream in("index.txt");
    if (!in.is_open()) {
        std::cerr << "\033[1;31mCould not open index.txt.\033[0m\n";
        return;
    }

    std::string line;
    std::cout << "\033[1;36mAvailable Lists:\033[0m\n";
    while (std::getline(in, line)) {
        std::cout << " - " << line << "\n";
    }
}

int main(int argc, char* argv[]) {
    enableANSIColors();
    if (argc < 2) {
        std::cerr << "\033[1;31mUsage: editor <command> [...]\033[0m\n";
        return 1;
    }

    std::string command = argv[1];

    try {
        if (command == "create_list" && argc >= 5) {
            std::string name = argv[2];
            int d, m, y;
            sscanf(argv[3], "%d.%d.%d", &d, &m, &y);
            Date date = { d, m, y };

            std::vector<std::string> tasks;
            for (int i = 4; i < argc; ++i) {
                tasks.push_back(argv[i]);
            }

            create_list(name, date, tasks);
        } else if (command == "delete_list" && argc == 3) {
            delete_list(argv[2]);
        } else if (command == "view_lists") {
            view_lists();
        } else {
            std::cerr << "\033[1;31mInvalid command or arguments.\033[0m\n";
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mException: " << e.what() << "\033[0m\n";
        return 1;
    }

    return 0;
}

