#include "TaskManager.h"
#include "Task.h"

void TaskManager::addTask(const std::string& desc, unsigned int prio) {
    tasks.push_back(Task(desc, prio));
    sort_tasks();
}
void TaskManager::add_existing_tasks(int ID, std::string desc, unsigned int prio, bool completed){
    addTask(desc, prio);
    tasks.back().set_ID(ID);
    tasks.back().set_state(completed);
}
std::string TaskManager::listTasks(){
    std::string result;
    if (tasks.size() == 0) result = "List is empty at the moment. Try adding a new element.";
    else {for (unsigned int counter = 0; counter < tasks.size(); counter++) result += std::to_string(counter + 1) + '.' + tasks[counter].print_Task() + '\n';}
    return result;
}

Function_Feedback TaskManager::markDone(int ID){  
    Function_Feedback f;
    f.description = "";
    f.success = false;
    for (unsigned int j = 0; j < tasks.size(); j++){
        if (tasks[j].get_ID() == ID){
        tasks[j].set_state(true);
        f.description = tasks[j].get_desc();
        f.success = true;
        return f;
        }
    }
    return f;
}

const std::vector<Task>& TaskManager::get_tasks() const {
    return tasks;
}

std::string TaskManager::delete_completed(){ 
    std::string result = "";
    for (int i = tasks.size() - 1; i >= 0; i--){
        if (tasks[i].get_state() == true) {
            result += " - " + tasks[i].get_desc() + "\n";
            tasks.erase(tasks.begin() + i);
        }
    }
    return result;
}

Function_Feedback TaskManager::delete_specific(int ID){   
    Function_Feedback f;
    f.success = false;
    f.description = "";
    for (unsigned int i = 0; i < tasks.size(); i++){
        if (tasks[i].get_ID() == ID) {
            f.description = tasks[i].get_desc();
            f.success = true;
            tasks.erase(tasks.begin() + i);
            return f;
        }
    }
    return f;
}

bool TaskManager::edit_priority(int ID, unsigned prio){  
    for (unsigned int j = 0; j < tasks.size(); j++){
        if (tasks[j].get_ID() == ID){
            tasks[j].set_prio(prio);
            sort_tasks();
            return true;
        }
    }
    return false;
}

void TaskManager::sort_tasks() {
    std::sort(tasks.begin(), tasks.end(), [](const Task& a, const Task& b) {
        if (a.get_prio() == b.get_prio()) return a.get_ID() < b.get_ID();
        return a.get_prio() > b.get_prio();
    });
}