#ifndef TODOLIST_H
#define TODOLIST_H

#include "Date.h"
#include "Task.h"
#include <vector>
#include <string>

class TodoList {
public:
    std::string name;
    Date date;
    std::vector<Task> tasks;

    TodoList(const std::string& name);
    void load();
    void save() const;
    void add_task(const std::string& desc);
    void complete_task(int id);
    void view_tasks() const;
    void check_and_autodelete();
};

#endif // TODOLIST_H
