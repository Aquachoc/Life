#include "content.hpp"


class Game{
    private:
        int nb_turn_;
        int nb_turn_max_;
        Board main_board_;
        rules_container rules_;
    public:
        Game(Board& b, rules_container& r, int nmax){
            main_board_=b;
            nb_turn_max_=nmax;
            rules_=r;
        };
        void next_step(){
        main_board_.init_board();
        main_board_.apply_rules(rules_);
        };

        void print_board()
        {
            vector<vector<bool>> to_display = main_board_.get_board();
            for(size_t i=0; i<to_display.size(); i++){
                for(size_t j=0; j<to_display[i].size(); j++)
            {
                if(to_display[i][j])
                    std::cout << "X";
                else
                    std::cout << "O";
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
        }

};

