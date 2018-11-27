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
    sf::Font font;
    sf::Text text;
    font.loadFromFile("ressources/arial.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    
    const sf::Time delta_refresh = sf::milliseconds(100);
    sf::RenderWindow window(sf::VideoMode(800, 800), "Life !");
    window.setFramerateLimit(20);
    sf::Music music;
    music.setLoop(true);
    
    
    vector<vector<Cell>> table_test;
    vector<Cell> line_test;
    int frog[16] = {0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0};

    for(size_t i = 0; i<16; i++){
        line_test.push_back(Cell(frog[i]));
        if(i%4==3){
            table_test.push_back(line_test);
            line_test.clear();
        }
    }
    rules_container r;
    Board board_test(table_test);
    Game g;//;(board_test, r, 4);
    t1 = clock.getElapsedTime();
    bool resume = false;
    
    grid<Cell> grid_buffer;

    Board board_tmp;
    int cursor = 0;
    vector<std::string> premade_figures;
    premade_figures = iogrid::get_names();
    size_t max_cursor = premade_figures.size();
    text.setString(premade_figures[cursor]);
    window.clear(sf::Color::White);
    g.print_board(window);
    window.draw(text);
    window.display();
    int cursor_x = 0;
    int cursor_y = 0;
    bool flag_save = 0;
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
                        case sf::Keyboard::Left:
                            cursor--;
                            if(cursor < 0)
                                cursor+=max_cursor;
                            text.setString(premade_figures[cursor]);
                        break;
                        case sf::Keyboard::Right:
                            cursor++;
                            if(cursor == max_cursor)
                                cursor=0;
                            text.setString(premade_figures[cursor]);
                        break;
                        case sf::Keyboard::L:
                            grid_buffer = iogrid::load_board(cursor);
                            board_tmp = Board(grid_buffer);

                            g.stamp_board(board_tmp,
                            sf::Mouse::getPosition(window).x * g.get_config().nb_cases_x /window.getSize().x, 
                            sf::Mouse::getPosition(window).y * g.get_config().nb_cases_y /window.getSize().y);
                            window.clear(sf::Color::White);
                            g.print_board(window);
                            window.draw(text);
                            window.display();
                            while(clock.getElapsedTime() < t1 + delta_refresh)
                            {
                                ;
                            }   
                        break;
                        case sf::Keyboard::D:
                            g.doge_toogle();
                            
                            if (!music.openFromFile("ressources/021dog.wav"))
                            return -1;
                            if(g.get_doge())
                            music.play();
                            else
                            music.pause();
                        break;

                        case sf::Keyboard::R:
                            g = Game();
                            resume=false;
                            music.pause();
                        break;
                        case sf::Keyboard::S:
                            window.clear(sf::Color::White);
                            cursor_x = sf::Mouse::getPosition(window).x * g.get_config().nb_cases_x /window.getSize().x;
                            cursor_y = sf::Mouse::getPosition(window).y * g.get_config().nb_cases_y /window.getSize().y;
                            while(window.isOpen() && !flag_save)
                            {
                                window.clear(sf::Color::White);
                                window.pollEvent(event);
                            
                            
                            gtools::select_rectangle(window, g.get_config().nb_cases_x, g.get_config().nb_cases_y,
                             cursor_x, cursor_y, sf::Mouse::getPosition(window).x * g.get_config().nb_cases_x /window.getSize().x,
                             sf::Mouse::getPosition(window).y * g.get_config().nb_cases_y /window.getSize().y);
                            g.print_board(window);
                            window.draw(text);
                            window.display();
                            while(clock.getElapsedTime() < t1 + delta_refresh)
                            {
                                ;
                            }
                            t1 = clock.getElapsedTime();
                            switch(event.type)
                            {
                                case sf::Event::Closed:
                                    window.close();
                                break;
                                case sf::Event::KeyPressed: 
                                    switch(event.key.code)
                                    {
                                        case sf::Keyboard::S:
                                            flag_save = true;
                                            grid_buffer = g.extract(cursor_x, cursor_y, sf::Mouse::getPosition(window).x * g.get_config().nb_cases_x /window.getSize().x,
                             sf::Mouse::getPosition(window).y * g.get_config().nb_cases_y /window.getSize().y);
                                            board_tmp = Board(grid_buffer);

                                            iogrid::save_board(board_tmp, "Custom" + std::to_string(max_cursor));
                                            premade_figures = iogrid::get_names();
                                            max_cursor++;
                                            cursor = max_cursor;
                                            text.setString(premade_figures[cursor]);
                                        break;
                                        default:
                                            flag_save = true;
                                        break;
                                    }
                                    break;
                                
                            }
                            }
                            flag_save = false;
                        break;
                    }
                break;
                case sf::Event::MouseButtonPressed:
                    if(!resume)
                    {
                        g.toogle(event.mouseButton.x * g.get_config().nb_cases_x /window.getSize().x, 
                        event.mouseButton.y * g.get_config().nb_cases_y /window.getSize().y);
                        window.clear(sf::Color::White);
                        
                        g.print_board(window);
                        window.draw(text);
                        window.display();
                    } 
                break;
            }
            
        }

        if(resume)
        {
            g.next_step();
            window.clear(sf::Color::White);
            g.print_board(window);
            window.draw(text);
            window.display();
        }
        else
        {
            window.clear(sf::Color::White);
            g.print_board(window);
            window.draw(text);
            window.display();
        }
        while(clock.getElapsedTime() < t1 + delta_refresh)
        {
            ;
        }
    

       // Sleep(100);*
    }
   
    
    //iogrid::save_board(board_test, "lol");
    return 0;
}
