#ifndef GAME_HPP
#define GAME_HPP

#include "content.hpp"
#include "graphics.hpp"
#include "parameters.hpp"
#include <fstream>
using std::vector;

class Game{
    private:
        int nb_turn_;
        int nb_turn_max_;
        Board main_board_;
        rules_container rules_;
        config_container config_;
       // sf::RenderWindow& main_frame_;
       bool doge_ = config_.doge;
    public:
    Game()
        {
            vector<vector<Cell>> tmp_board;
            vector<Cell> tmp_line;
            for(unsigned int i = 0; i < config_.nb_cases_x; i++)
            {
                for(unsigned int j = 0; j < config_.nb_cases_y; j++)
                {
                    tmp_line.push_back(Cell(false));
                }
                tmp_board.push_back(tmp_line);
                tmp_line.clear();
            }
            main_board_ = Board(tmp_board);
        };

        Game(Board& b, rules_container& r, int nmax){
            vector<vector<Cell>> tmp_board;
            vector<Cell> tmp_line;
            main_board_ = b;
            /*for(unsigned int i = 0; i < config_.nb_cases_x; i++)
            {
                for(unsigned int j = 0; j < config_.nb_cases_y; j++)
                {
                    tmp_line.push_back(Cell(false));
                }
                tmp_board.push_back(tmp_line);
                tmp_line.clear();
            }
            Board main_board_(tmp_board);*/
            nb_turn_max_=nmax;
            rules_=r;
        };

        
        void toogle(unsigned int x, unsigned int y)
        {
            main_board_.toogle(x,y);
        }
        void next_step(){
        main_board_.init_board();
        main_board_.apply_rules(rules_);
        };
        
        void print_board(sf::RenderWindow& main_frame)
        {
           // main_frame.clear(sf::Color::White);

            vector<vector<bool>> to_display = main_board_.get_board();
            for(size_t i=0; i<to_display.size(); i++){
                for(size_t j=0; j<to_display[i].size(); j++)
            {
                if(to_display[i][j])
                    gtools::set_square(main_frame, config_.nb_cases_x, config_.nb_cases_y, i, j, true, doge_);
            }
        }

        gtools::grid(main_frame, config_.nb_cases_x, config_.nb_cases_y);
        }
        void doge_toogle()
        {
            doge_= !doge_;
        };
        bool get_doge()
        {
            return doge_;
        };
        config_container get_config()
        {
            return config_;
        };
        void stamp_board(const Board& b, const unsigned int x, const unsigned int y)
        {
            main_board_.stamp_board(b, x, y);
        }

        grid<Cell> extract(const size_t i, const size_t j, const size_t k, const size_t l)
        {
            if(k<i)
                return extract(k,j,i,l);
            else if(l<j)
                return extract(i,l,k,j);
            vector<Cell> line;
            grid<Cell> buffer;
            for(size_t x=i; x<k+1; x++)
            {
                for(size_t y=j; y<l+1; y++)
                {
                    line.push_back(Cell(main_board_.get_cell_state(x,y)));
                }
                buffer.push_back(line);
                line.clear();
            }
            return buffer;
        }
};



namespace iogrid{
    bool save_board(Board b, std::string name)
    {
        std::fstream save_file ("ressources/save.txt", std::ios::in | std::ios::app);
        if(save_file.is_open())
        {
            
            save_file << name << " " << b.get_size_x() << " " << b.get_size_y() << " ";
            for(size_t i=0; i < b.get_size_x(); ++i){
                for(size_t j=0; j < b.get_size_y(); ++j)
                    save_file << (b.get_cell_state(i, j) ? '1' : '0');
                    //save_file << " ";
                    }

            save_file << std::endl;
            save_file.close();
        }
        else
        std::cout << "error";
    }
    vector<vector<Cell>> load_board(int cursor=0)
    {
        std::fstream save_file ("ressources/save.txt", std::ios::in | std::ios::app);
        vector<vector<Cell>> cells;
        vector<Cell> line_tmp;
        if(save_file.is_open())
        {
            
            std::string buffer;
            for(int _  = 0; _<cursor; _++, getline(save_file, buffer));
            save_file >> buffer;
            std::cout << "\n" << buffer;
            save_file >> buffer;
            std::cout << "\n" << buffer;
            size_t x = atoi(buffer.c_str());
            save_file >> buffer;
            std::cout << "\n" << buffer;
            size_t y = atoi(buffer.c_str());
            save_file >> buffer;
            std::cout << "\n";
            for(unsigned i = 0; i<x; i++){
                for(unsigned j=0; j<y; j++)
                    {
                        char c = buffer[y*i+j];
                        line_tmp.push_back(c=='1' ? Cell(true) : Cell(false));
                        std::cout << c;
                    }
                cells.push_back(line_tmp);
                line_tmp.clear();
            }
            save_file.close();
        }

        return cells;
    }
    vector<std::string> get_names(){
        std::fstream save_file ("ressources/save.txt");
        std::string buffer_string;
        std::string concat;
        vector<std::string> buffer;

        if(save_file.is_open())
        {  
            
            while(!save_file.eof())
            {   
                if(!save_file.eof())
                save_file >> buffer_string;
                if(!save_file.eof())
                save_file >> concat;

                buffer_string += " (" + concat;
                if(!save_file.eof())
                save_file >> concat;
                buffer_string += "x" + concat +")";
                if(!save_file.eof())
                save_file >> concat;
                buffer.push_back(buffer_string);
                std::cout << buffer_string << std::endl;
               
            }
            if(buffer.size())
                buffer.pop_back();
            save_file.close();
        }
        return buffer;
    }
}

#endif