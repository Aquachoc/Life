#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP
#include <SFML/Graphics.hpp>

// gtools (graphical tools) will contain all the functions for display
namespace gtools{

    // prints line between (x1,y1) and (x2,y2), pixel coordinate from the top left corner
    void print_line(sf::RenderWindow& window, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
    {
        sf::VertexArray line_tmp(sf::Lines, 2);
        line_tmp[0].position = sf::Vector2f(x1, y1);
        line_tmp[1].position = sf::Vector2f(x2, y2);
        line_tmp[0].color = sf::Color::Black;
        line_tmp[1].color = sf::Color::Black;
        window.draw(line_tmp);
    };
    
    // draws full window vertical line at x1
    void print_vline(sf::RenderWindow& window, unsigned int x1)
    {
        print_line(window, x1, 0, x1, window.getSize().y);
    };

    void print_hline(sf::RenderWindow& window, unsigned int y1)
    {
        print_line(window, 0, y1, window.getSize().x, y1);
    };

    // Draws the game main grid 
    void grid(sf::RenderWindow& window, unsigned int nb_cases_x, unsigned int nb_cases_y)
    {
        // fetches dimensions of the window
        unsigned int x = window.getSize().x;
        unsigned int y = window.getSize().y;
        //computes the pixel size of each cell
        unsigned int side_x = x/nb_cases_x;
        unsigned int side_y = y/nb_cases_y;
        for(unsigned int i = 1; i < nb_cases_x; ++i)
        {
            print_vline(window, i*side_x);
        }
        for(unsigned int i = 1; i < nb_cases_y; ++i)
        {
            print_hline(window, i*side_y);
        }
    };

    // state = 1 for active square, =0 for dead square; doge is the doge indicator
    void set_square(sf::RenderWindow& window, unsigned int nb_cases_x, 
    unsigned int nb_cases_y, unsigned int coord_x, unsigned int coord_y, bool state, bool doge = false)
    {
        static bool load_textures = false;
        static sf::Texture ann_doge;
        static sf::Sprite sprite;

        // On first run loads the doge sprite
        if(!load_textures)
            if (ann_doge.loadFromFile("ressources/doge.png"))
                sprite.setTexture(ann_doge);

        load_textures = true;
        // fetches dimensions of the window
        unsigned int x = window.getSize().x;
        unsigned int y = window.getSize().y;
        //computes the pixel size of each cell
        unsigned int side_x = x/nb_cases_x;
        unsigned int side_y = y/nb_cases_y;
        sf::VertexArray square_tmp(sf::Quads, 4);
        // sets the square
        square_tmp[0].position = sf::Vector2f(side_x*coord_x, side_y*coord_y);
        square_tmp[1].position = sf::Vector2f(side_x*(coord_x+1), side_y*coord_y);
        square_tmp[2].position = sf::Vector2f(side_x*(coord_x+1), side_y*(coord_y+1));
        square_tmp[3].position = sf::Vector2f(side_x*coord_x, side_y*(coord_y+1));
        // Paints the square when there is no doge
        if(!doge)
        {
        // Fills the square black for alive cell, white for dead cell
        switch(state){
            case true:
                square_tmp[0].color = sf::Color::Black;
                square_tmp[1].color = sf::Color::Black;
                square_tmp[2].color = sf::Color::Black;
                square_tmp[3].color = sf::Color::Black;
                window.draw(square_tmp);
                break;
            case false:
                square_tmp[0].color = sf::Color::White;
                square_tmp[1].color = sf::Color::White;
                square_tmp[2].color = sf::Color::White;
                square_tmp[3].color = sf::Color::White;
                window.draw(square_tmp);
            break;
        }    
        }
        // else we display the doge
        else{
    sprite.setPosition(sf::Vector2f(side_x*coord_x, side_y*coord_y));
    sprite.setScale(sf::Vector2f(static_cast<float>(side_x)/265, static_cast<float>(side_y)/256));
    window.draw(sprite);
        }

        
    };

    // draws a red rectangle around the area between the couple (i,j) and (k,l)
    // the function is order safe and rearranges the parameters so that (i,j) is the top left corner
    void select_rectangle(sf::RenderWindow& w, unsigned int nb_cases_x, unsigned int nb_cases_y, unsigned int i,unsigned int j, 
        unsigned int k, unsigned int l, unsigned int thickness = 10)
    {
        //rearranges the parameters
        if(i>k)
            select_rectangle(w, nb_cases_x, nb_cases_y, k, j, i, l);
        else if(j>l)
            select_rectangle(w, nb_cases_x, nb_cases_y, i, l, k, j);
        else{
        // computes the pixel size of each cell
        unsigned int side_x = w.getSize().x / nb_cases_x;
        unsigned int side_y = w.getSize().y / nb_cases_y;
        // defines the four sides of the rectangle
        // their position has an offset of half their thickness to make them centered on the grid (no offset on the border of the grid)
        sf::RectangleShape line1(sf::Vector2f((k-i+1)*side_x+thickness*(i>0 && k!=nb_cases_y), thickness));
        sf::RectangleShape line2(sf::Vector2f((k-i+1)*side_x+thickness*(i>0 && k!=nb_cases_y), thickness));
        sf::RectangleShape line3(sf::Vector2f((l-j+1)*side_x+thickness*(j>0 && l!=nb_cases_y), thickness));
        sf::RectangleShape line4(sf::Vector2f((l-j+1)*side_x+thickness*(j>0 && l!=nb_cases_y), thickness));
        // sets line 3 and 4 horizontally
        line3.rotate(90);
        line4.rotate(90);
        // sets the position of each line with respect for the grids borders and thickness
        line1.setPosition(i > 0 ? side_x*i-thickness/2: 0, j > 0 ? side_y*j-thickness/2 : 0);
        line2.setPosition(i > 0 ? side_x*i-thickness/2 : 0, side_y*(l+1)-thickness/2);
        line3.setPosition(side_x*i+thickness/2, j > 0 ? side_y*j-thickness/2 : 0);
        line4.setPosition(k == nb_cases_x ? w.getSize().x : side_x*(k+1)+thickness/2 , j > 0 ? side_y*j-thickness/2 : 0);
        // paints the lines in red
        line1.setFillColor(sf::Color::Red);
        line2.setFillColor(sf::Color::Red);
        line3.setFillColor(sf::Color::Red);
        line4.setFillColor(sf::Color::Red);

        // displays the lines
        w.draw(line1);
        w.draw(line2);
        w.draw(line3);
        w.draw(line4);
        }
    }

}
#endif