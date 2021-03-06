#ifndef PARAMETERS_HPP // preprocessing security
#define PARAMETERS_HPP

#include <vector>
#include <iostream>
#include <fstream>
using std::vector;

// container for the parameters of the game
// the parameters are fetched from ./ressources/config.txt
// the line order cannot be changed: first line is assumed to be size_x, second size_y
struct config_container{
    unsigned int nb_cases_x = 20;
    unsigned int nb_cases_y = 20;
    unsigned int res_x = 800;
    unsigned int res_y = 800;
    bool doge = false;
    config_container();
};
config_container::config_container(){
    std::ifstream file("ressources/config.txt", std::ios::in);
    std::string arg;
    if(file){
        // we remove everything before the = char
        while(file.get()!='=');
        file >> arg;
        nb_cases_x = atoi(arg.c_str());
        while(file.get()!='=');
        file >> arg;
        nb_cases_y = atoi(arg.c_str());
        while(file.get()!='=');
        file >> arg;
        res_x = atoi(arg.c_str());
        while(file.get()!='=');
        file >> arg;
        res_y = atoi(arg.c_str());
        
        file.close();
    }
    else  
        std::cerr << "Config error" << std::endl;
};
#endif