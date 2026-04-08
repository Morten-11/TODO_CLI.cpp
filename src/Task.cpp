#include <Task.h>

int Task::ID_Counter = 1;


Task::Task(const std::string& description, unsigned int prio): ID(ID_Counter++), description(description), completed(false), priority(prio){}
void Task::set_ID_Counter(int value) {
    ID_Counter = value;
}

std::string Task::print_Task() const {
    std::string p = "[";
    if (completed == true) p += "x";
    else p += " ";
    p += "] " + description + " (ID: " + std::to_string(ID) + ") {prio: " + std::to_string(priority) + "}";
    return p;
}
void Task::mark_done(){ 
    completed = true; 
}
int Task::get_ID() const {
    return ID;
}
const std::string& Task::get_desc() const {
    return description;
}
bool Task::get_state() const {
    return completed;
}
unsigned int Task::get_prio() const {
    return priority;
}
void Task::set_ID(int id){
    ID = id;
}
void Task::set_state(bool state){
    completed = state;
}
void Task::set_prio(unsigned int prio){
    priority = prio;
}    