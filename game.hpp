#include "content.hpp"
#include "graphics.hpp"
#include "parameters.hpp"
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
        }
};

