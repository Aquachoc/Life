#include <vector>
#include <iostream>
#include <fstream>
using std::vector;

struct config_container{
    unsigned int nb_cases_x = 20;
    unsigned int nb_cases_y = 20;
    bool doge = false;
    config_container();
};
config_container::config_container(){
    std::ifstream file("ressources/config.txt", std::ios::in);
    std::string arg;
    if(file){
        while(file.get()!='=');
                file >> arg;
                nb_cases_x = atoi(arg.c_str());
        while(file.get()!='=');
                file >> arg;
                nb_cases_y = atoi(arg.c_str());
        file.close();
    }
    else  
        std::cerr << "Config error" << std::endl;
};