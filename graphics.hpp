#include <SFML/Graphics.hpp>

namespace gtools{

    void print_line(sf::RenderWindow& window, unsigned int x1, unsigned int y1, unsigned int x2, unsigned int y2)
    {
        sf::VertexArray line_tmp(sf::Lines, 2);
        line_tmp[0].position = sf::Vector2f(x1, y1);
        line_tmp[1].position = sf::Vector2f(x2, y2);
        line_tmp[0].color = sf::Color::Black;
        line_tmp[1].color = sf::Color::Black;
        window.draw(line_tmp);
    };

    void print_vline(sf::RenderWindow& window, unsigned int x1)
    {
        print_line(window, x1, 0, x1, window.getSize().y);
    };

    void print_hline(sf::RenderWindow& window, unsigned int y1)
    {
        print_line(window, 0, y1, window.getSize().x, y1);
    };

    void grid(sf::RenderWindow& window, unsigned int nb_cases_x, unsigned int nb_cases_y)
    {
        unsigned int x = window.getSize().x;
        unsigned int y = window.getSize().y;
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

    void set_square(sf::RenderWindow& window, unsigned int nb_cases_x, 
    unsigned int nb_cases_y, unsigned int coord_x, unsigned int coord_y, bool state, bool doge = false)
    {
        static bool load_textures = false;
        static sf::Texture ann_doge;
        static sf::Sprite sprite;
        if(!load_textures)
        { 
        
        if (ann_doge.loadFromFile("doge.png"))
{
    
    sprite.setTexture(ann_doge);
    
}

        }
        load_textures = true;
        unsigned int x = window.getSize().x;
        unsigned int y = window.getSize().y;
        unsigned int side_x = x/nb_cases_x;
        unsigned int side_y = y/nb_cases_y;
        sf::VertexArray square_tmp(sf::Quads, 4);
        square_tmp[0].position = sf::Vector2f(side_x*coord_x, side_y*coord_y);
        square_tmp[1].position = sf::Vector2f(side_x*(coord_x+1), side_y*coord_y);
        square_tmp[2].position = sf::Vector2f(side_x*(coord_x+1), side_y*(coord_y+1));
        square_tmp[3].position = sf::Vector2f(side_x*coord_x, side_y*(coord_y+1));
        if(!doge)
        {
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
        }       }
        else{
    sprite.setPosition(sf::Vector2f(side_x*coord_x, side_y*coord_y));
    sprite.setScale(sf::Vector2f(static_cast<float>(side_x)/265, static_cast<float>(side_y)/256));
    window.draw(sprite);
        }

        
    };

    


}