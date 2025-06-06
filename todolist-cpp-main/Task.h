#ifndef TASK_H
#define TASK_H

#include <string>

class Task {
public:
    int id;
    std::string description;
    bool completed;

    Task(int _id, const std::string& desc, bool comp = false);
    std::string to_string() const;
    static Task from_string(const std::string& line);
};

#endif // TASK_H
