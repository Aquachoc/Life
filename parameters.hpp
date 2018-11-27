#include <vector>
#include <iostream>
#include <fstream>
using std::vector;

struct config_container{
    int size = 200;
    unsigned int nb_cases_x = 10;
    unsigned int nb_cases_y = 10;
    bool doge = false;
    config_container();
};
config_container::config_container(){
    std::ifstream file("config.txt", std::ios::in);
    if(file){
        std::string parameter;
        file >> parameter;
        
        file.close();
    }
    else  
        std::cerr << "Config error" << std::endl;
};