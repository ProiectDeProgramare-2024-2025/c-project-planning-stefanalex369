#include "TodoList.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <filesystem>

TodoList::TodoList(const std::string& list_name) : name(list_name) {}

void TodoList::load() {
    std::ifstream in("lists/" + name + ".txt");
    if (!in.is_open()) return;

    std::string date_line;
    std::getline(in, date_line);
    sscanf(date_line.c_str(), "%d.%d.%d", &date.day, &date.month, &date.year);

    std::string line;
    while (std::getline(in, line)) {
        tasks.push_back(Task::from_string(line));
    }
    in.close();
}

void TodoList::save() const {
    std::ofstream out("lists/" + name + ".txt");
    out << date.day << "." << date.month << "." << date.year << "\n";
    for (const auto& task : tasks) {
        out << task.to_string() << "\n";
    }
}

void TodoList::add_task(const std::string& desc) {
    int id = tasks.empty() ? 1 : tasks.back().id + 1;
    tasks.emplace_back(id, desc, false);
    save();
}

void TodoList::complete_task(int id) {
    for (auto& task : tasks) {
        if (task.id == id) {
            task.completed = true;
            break;
        }
    }
    save();
    check_and_autodelete();
}

void TodoList::check_and_autodelete() {
    bool all_completed = true;
    for (const auto& task : tasks) {
        if (!task.completed) {
            all_completed = false;
            break;
        }
    }

    if (all_completed) {
        std::cout << "\033[1;31mAll tasks completed. Auto-deleting the list: " << name << "\033[0m\n";
        std::filesystem::remove("lists/" + name + ".txt");

        // Actualizare index.txt
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
    }
}

void TodoList::view_tasks() const {
    std::cout << "Tasks " << date.day << "." << date.month << "." << date.year << "\n";
    for (const auto& task : tasks) {
        if (task.completed)
            std::cout << "\033[1;32m" << task.to_string() << "\033[0m\n"; // verde
        else
            std::cout << task.to_string() << "\n";
    }
}
