#include "TodoList.h"
#include <iostream>
#include <stdexcept>
#include <windows.h>
void enableANSIColors() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}

int main(int argc, char* argv[]) {
    enableANSIColors();
    if (argc < 3) {
        std::cerr << "\033[1;31mUsage: manager <command> <list_name> [args]\033[0m\n";
        return 1;
    }

    std::string command = argv[1];
    std::string list_name = argv[2];

    try {
        TodoList list(list_name);
        list.load();

        if (command == "add_task" && argc == 4) {
            list.add_task(argv[3]);
        } else if (command == "complete_task" && argc == 4) {
            int id = std::stoi(argv[3]);
            list.complete_task(id);
        } else if (command == "view_tasks") {
            list.view_tasks();
        } else {
            std::cerr << "\033[1;31mUnknown command.\033[0m\n";
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << "\033[1;31mException: " << e.what() << "\033[0m\n";
        return 1;
    }

    return 0;
}
