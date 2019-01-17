#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <SFML/Audio.hpp>
#include "game.hpp"
using namespace std;

int main()
{
    
    sf::Clock clock; //used for time
    sf::Time t1; //main measure of time
    const sf::Time delta_refresh = sf::milliseconds(100); //refresh delay for the main event handle
    sf::Font font; //for name display
    sf::Text text; // actual text
    auto wipe_color = sf::Color::White;
    font.loadFromFile("ressources/arial.ttf");
    text.setFont(font);
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::Red);
    sf::Music music;
    music.setLoop(true);
    sf::RenderWindow window(sf::VideoMode(800, 800), "Life !"); //main window
    window.setFramerateLimit(20); //framerate
    
    Game g; //our main Game
    t1 = clock.getElapsedTime(); //ready the clock
    bool resume = false; //pause flag
    bool step = false;
    grid<Cell> grid_buffer; //our ready to use memory

    Board board_tmp; //out ready to use buffer
    int cursor = 0; //cursor for the text 
    vector<std::string> premade_figures; //names of all saves figures
    premade_figures = iogrid::get_names(); //init
    size_t max_cursor = premade_figures.size();
    text.setString(premade_figures[cursor]); //init the text
    window.clear(wipe_color); //prepare clean window
    g.print_board(window); //display initial setup
    window.draw(text);
    window.display();
    int cursor_x = 0; //used for save coordinates
    int cursor_y = 0;
    bool flag_save = 0; //used to handle the save loop
    while(window.isOpen())
    {
        
        t1 = clock.getElapsedTime(); //set time
        sf::Event event; //get new event
        while (window.pollEvent(event)) //refresh it
        {
            switch(event.type)
            {
                case sf::Event::Closed: //close window
                    window.close();
                break;
                case sf::Event::KeyPressed: //if key
                    switch(event.key.code)
                    {
                        case sf::Keyboard::N:
                        step = true;
                        break;
                        case sf::Keyboard::Space: //space for pause
                            resume = !resume;
                        break;
                        case sf::Keyboard::Left: //LR to navigate
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
                        case sf::Keyboard::L: //Load the selected figure where the cursor is (top left corner)
                            grid_buffer = iogrid::load_board(cursor);
                            board_tmp = Board(grid_buffer); //prepare the selected board
                            g.stamp_board(board_tmp,
                            sf::Mouse::getPosition(window).x * g.get_config().nb_cases_x /window.getSize().x, 
                            sf::Mouse::getPosition(window).y * g.get_config().nb_cases_y /window.getSize().y); //replace the right area with the selected save
                            window.clear(wipe_color); //main loop
                            g.print_board(window);
                            window.draw(text);
                            window.display();
                            while(clock.getElapsedTime() < t1 + delta_refresh) //wait
                            {
                                ;
                            }   
                        break;
                        case sf::Keyboard::D: //It smells like wet dog
                            g.doge_toogle();
                            wipe_color = g.get_doge() ? sf::Color::Black : sf::Color::White;
                            if (!music.openFromFile("ressources/021dog.wav"))
                            return -1;
                            if(g.get_doge())
                            music.play();
                            else
                            music.pause();
                        break;

                        case sf::Keyboard::R: //reset
                            g = Game();
                            resume=false;
                            wipe_color = g.get_doge() ? sf::Color::Black : sf::Color::White;
                            music.pause();
                        break;
                        case sf::Keyboard::S: //enter save
                            cursor_x = sf::Mouse::getPosition(window).x * g.get_config().nb_cases_x /window.getSize().x; //get initial position
                            cursor_y = sf::Mouse::getPosition(window).y * g.get_config().nb_cases_y /window.getSize().y;
                            while(window.isOpen() && !flag_save) //subloop escape by all, validate with S
                            {
                                window.clear(wipe_color);
                                while(window.pollEvent(event) && event.type != sf::Event::KeyPressed && event.type != sf::Event::Closed);
                            
                            
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
                                            text.setString(premade_figures[cursor-1]);
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
                        window.clear(wipe_color);
                        
                        g.print_board(window);
                        window.draw(text);
                        window.display();
                    } 
                break;
            }
            
        }

        if(resume || step)
        {
            g.next_step();
            window.clear(wipe_color);
            g.print_board(window);
            window.draw(text);
            window.display();
            step = false;
        }
        else
        {
            window.clear(wipe_color);
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
