#pragma once
#include <string>

class Task{
private:
    int ID;
    std::string description;
    bool completed;
    unsigned int priority;

    static int ID_Counter;

public:
    Task(const std::string& description, unsigned int prio);

    static void set_ID_Counter(int value);
    std::string print_Task() const;
    void mark_done();

    int get_ID() const;
    const std::string& get_desc() const;
    bool get_state() const;
    unsigned int get_prio() const;

    void set_ID(int id);
    void set_state(bool state);
    void set_prio(unsigned int prio);
};