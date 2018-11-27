#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
#include <SFML/Audio.hpp>
#include "game.hpp"
using namespace std;

int main()
{
    
    config_container config;
    sf::Clock clock;
    sf::Time t1;
    sf::Time t2 = sf::milliseconds(100);
    sf::RenderWindow window(sf::VideoMode(800, 800), "Life !");
     window.setFramerateLimit(20);
    sf::Music music;
    music.setLoop(true);

    vector<vector<Cell>> table_test;
    vector<Cell> line_test;
    int frog[20] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0,0,0,0,0};

    for(size_t i = 0; i<20; i++){
        line_test.push_back(Cell(frog[i]));
        if(i%4==3){
            table_test.push_back(line_test);
            line_test.clear();
        }
    }
    rules_container r;
    Board board_test(table_test);
    Game g; //(board_test, r, 4);
    t1 = clock.getElapsedTime();
    bool resume = false;
    window.clear(sf::Color::White);
    g.print_board(window);
    window.display();
    while(window.isOpen())
    {
        
        t1 = clock.getElapsedTime();
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                break;
                case sf::Event::KeyPressed:
                    switch(event.key.code)
                    {
                        case sf::Keyboard::Space:
                            resume = !resume;
                        break;
                        case sf::Keyboard::D:
                            g.doge_toogle();
                            window.clear(sf::Color::White);
                            g.print_board(window);
                            window.display();
                            
                            if (!music.openFromFile("021dog.wav"))
                            return -1;
                            if(g.get_doge())
                            music.play();
                            else
                            music.pause();
                        break;

                    }
                break;
                case sf::Event::MouseButtonPressed:
                    if(!resume)
                    {g.toogle(event.mouseButton.x * config.nb_cases_x /window.getSize().x, 
                    event.mouseButton.y * config.nb_cases_y /window.getSize().y);
                    window.clear(sf::Color::White);
    g.print_board(window);
    window.display();
                    } 
                break;
            }
            
        }
        if(resume)
        {
        g.next_step();
        g.print_board(window);
        window.display();
        
        while(clock.getElapsedTime() < t1 + t2)
        {
            ;
        }
        window.clear(sf::Color::White);
    }
       // Sleep(100);*
    }
    return 0;
}
