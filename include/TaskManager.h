#pragma once
#include <algorithm>
#include <string>
#include <vector>
#include <iostream>
#include "Task.h"

struct Function_Feedback {
    bool success;
    std::string description;
};

class TaskManager{
private:
    std::vector<Task> tasks;
public:
    void addTask(const std::string& desc, unsigned int prio);
    void add_existing_tasks(int ID, std::string desc, unsigned int prio, bool completed);

    std::string listTasks();
    Function_Feedback markDone(int ID);

    const std::vector<Task>& get_tasks() const;

    std::string delete_completed();

    Function_Feedback delete_specific(int ID);

    bool edit_priority(int ID, unsigned prio);

    void sort_tasks();
};