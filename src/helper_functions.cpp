#include "helper_functions.h"

void load_File(TaskManager& T){
    std::ifstream File("output/TODO_LIST.txt");
    std::string line;
    int new_ID;
    bool new_completed;
    std::string new_desc;
    unsigned int new_prio;
    int max_ID = 1;
    
    if (!File) return;
    else { 
        while (getline(File, line)){
            std::string id_str;
            std::string completed_str;
            std::string prio_str;
            std::istringstream iss(line);

            getline(iss, id_str, ';');
            getline(iss, completed_str, ';');
            getline(iss, prio_str, ';');
            getline(iss, new_desc);

            new_ID = stoi(id_str);
            if (completed_str == "0") new_completed = false;
            else new_completed = true;
            new_prio = stoi(prio_str);

            T.add_existing_tasks(new_ID, new_desc, new_prio, new_completed);
            if (new_ID > max_ID) max_ID = new_ID;
        }  
    }
    Task::set_ID_Counter(max_ID + 1);
}

void write_File(TaskManager& T){
    std::ofstream File("output/TODO_LIST.txt");

    if (!File) {
        std::cout << "failed to open the file" << std::endl;
    } else {
        for (unsigned counter = 0; counter < T.get_tasks().size(); counter++) File << T.get_tasks()[counter].get_ID() << ';' << T.get_tasks()[counter].get_state() << ';' << T.get_tasks()[counter].get_prio() << ';' << T.get_tasks()[counter].get_desc() << std::endl;
    }
}