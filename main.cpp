#include <iostream>
#include "game.hpp"

using namespace std;

int main()
{
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
    Game g(board_test, r, 5);
    g.print_board();

        g.next_step();
        g.print_board();
       g.next_step();
        g.print_board();
               g.next_step();
        g.print_board();
    std::cout<<table_test[0][0].get_state();
    return 0;
}
