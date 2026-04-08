#include "Task.h"
#include "TaskManager.h"
#include "helper_functions.h"


int main(){
    TaskManager T;
    std::string instructions = "- 'add' <item> - to add an item to your list\n- 'list' - to see your existing list\n- 'done' <ID> - to check off an item on your list\n- 'priority' <ID> - to edit a priority value of a specific task\n- 'delete' <ID> - to delete a specific task\n- 'delete' - to delete all completed tasks\n- 'exit' - to exit the program";
    std::cout << "\n" + std::string(38, '_') + "\n " + std::string(5, '_') + "\t" + std::string(5, '_') + "\t___     " + std::string(5, '_') + "   " + std::string(5, '_') + "\n" 
    + "|_   _||  _  | |   \\   |  _  | |  ___|\n"
    + "  | |  | | | | | |\\ \\  | | | | | |___\n" 
    + "  | |  | | | | | | ) ) | | | | |___  |\n"
    + "  | |  | |_| | | |/ /  | |_| |  ___| |\n"
    + "  |_|  |_____| |___/   |_____| |_____|\n" + std::string(38, '_') + "\nWrite\n" << instructions << std::endl;

    load_File(T);
    std::string action;
    std::string add_info;
    std::string input_sentence;

    while (1){
        action = "";
        add_info = "";
        getline(std::cin, input_sentence);
        long unsigned int counter = 0;
        while (counter < input_sentence.length() && input_sentence[counter] != ' '){
            action += input_sentence[counter];
            counter++;
            
        } 
        counter++;
        if (action == "add" || action == "done" || action == "delete" || action == "priority"){
            while (counter < input_sentence.length()) {
                add_info += input_sentence[counter];
                counter++;
            }
        }
        if (action == "exit") {
            write_File(T);
            break;
        }
        else if (action == "list") std::cout << T.listTasks();
        else if (action == "add"){
            while (1){
                if (add_info.empty()) {
                    std::cout << "no description has been entered..." << std::endl;
                    break;
                }

                std::string input;
                std::cout << "State the priority of this task. If none is entered, the default will be 3. Priority ranges from 1 (not important) up to 5 (very important): ";
                getline(std::cin, input);

                if (input.empty()) {
                    T.addTask(add_info, 3);
                    break;
                }
                try{
                    int p = stoi(input);
                    if (p > 5 || p < 1) std::cout << "Error, this is not a valid priority value. Please try again" << std::endl;
                    else {
                        T.addTask(add_info, p);
                        break;
                    }
                }
                catch(std::invalid_argument&){
                    std::cout << "Priority is measure in integers from 1 to 5!" << std::endl;
                    continue;
                } 
            }
        } 
        else if (action == "done"){
            try{
                int ID = std::stoi(add_info);
                Function_Feedback f = T.markDone(ID);
                if (!f.success) std::cout << "ID is not valid or out of range." << std::endl;
                else std::cout << "The task '" << f.description << " has been checked off." << std::endl;
            }
            catch(std::invalid_argument&){
                std::cout << "Not a valid ID, only integers are allowed as ID"<< std::endl;
                continue;
            }     
        }
        else if (action == "delete"){   
            if (!add_info.empty()) {
                try{
                    int del_ID = std::stoi(add_info);
                    Function_Feedback f = T.delete_specific(del_ID);
                    if(!f.success) std::cout << "Error, the entered ID does not exist. Enter 'list' to see all current tasks and their respective ID." << std::endl;
                    else std::cout << "The task " << f.description << " has been deleted successfully." << std::endl; 
                }
                catch(std::invalid_argument&){
                    std::cout << "Not a valid ID, only integers are allowed as ID" << std::endl;
                    continue;
                }  
            }
            else std::cout << "The following tasks have been deleted:\n" << T.delete_completed();
        }
        else if (action == "priority"){
            while (1){
                if (add_info.empty()) {
                    std::cout << "no ID has been entered..." << std::endl;
                    break;
                }
                try{
                    int edit_ID = stoi(add_info);
                    unsigned int new_prio;
                    std::string new_prio_str;

                    std::cout << "Enter new priority value: ";
                    getline(std::cin, new_prio_str);
                    
                    new_prio = stoi(new_prio_str);
                    if (new_prio > 0 && new_prio < 6) {
                        if (!T.edit_priority(edit_ID, new_prio)) std::cout << "ID could not be found." << std::endl;
                        break;
                    }else {
                        std::cout << "Priority value is not valid." << std::endl;
                        continue;
                    }
                }catch(std::invalid_argument&){
                    std::cout << "Error, no integer was entered." << std::endl;
                    continue;
                }
            }  
        }
        else std::cout << "Invalid action. Please enter one of the following actions:\n" << instructions << std::endl;
    }
    return 0;
}