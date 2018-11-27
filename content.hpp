#include <vector>
#include <iostream>
#include <SFML/Graphics.hpp>
using std::vector;
template<class T>
using grid = vector<vector<T>>;

typedef struct{
    unsigned int survival_min=2;
    unsigned int survival_max=3;
    unsigned int birth_min=3;
    unsigned int birth_max=3;
}rules_container;

class Cell{
private:
    bool state_;
    //bool future_state_;
    unsigned int nb_neigh_alive_ = 0;
public:
    Cell(bool s){
        state_=s;
    };
    Cell(const Cell&) = default;
    void reset_neigh(){nb_neigh_alive_=0;};
    void incr_neigh(){nb_neigh_alive_++;};
    void decr_neigh(){nb_neigh_alive_--;};
    void set_state(bool s){state_ = s;};
    void toogle(){ state_ = !state_;};
   // void set_future(bool s){future_state_ = s;};

    unsigned int get_neigh(){return nb_neigh_alive_;};
    bool get_state(){return state_;};
    //int get_future(){return future_state_;};

};

class Board{
private:
    unsigned int nb_turn_;
    unsigned int dim_x_;
    unsigned int dim_y_;
    vector<vector<Cell>> cells_;
public:
    Board(){};
    Board(vector<vector<Cell>>& v){
        cells_=v;
        dim_x_=v.size();
        dim_y_=v[0].size();
        };
        
    vector<vector<bool>> get_board()
    {
               vector<bool> line;
        vector<vector<bool>> arr;
        for(size_t i=0; i<dim_x_; i++)
        {
            for(size_t j=0; j<dim_y_; j++)
            {
                line.push_back(cells_[i][j].get_state());
            }
            arr.push_back(line);
            line.clear();
        }
        return arr;
    }
    void toogle(unsigned int x, unsigned int y)
    {
        cells_[x][y].toogle();
    }
    unsigned int get_size_x()
    {
        return dim_x_;
    }
    unsigned int get_size_y()
    {
        return dim_y_;
    }
    void init_board(){
        for(size_t i=0; i<dim_x_; i++){
            for(size_t j=0; j<dim_y_; j++){
                if(!(cells_[i][j].get_state()))
                    continue;
                if(i>0 && j>0)
                    cells_[i-1][j-1].incr_neigh();
                if(i>0)
                    cells_[i-1][j].incr_neigh();
                if(i>0 && j+1<dim_y_)
                    cells_[i-1][j+1].incr_neigh();
                if(j>0)
                    cells_[i][j-1].incr_neigh();
                if(j+1<dim_y_)
                    cells_[i][j+1].incr_neigh();
                if(i+1<dim_x_ && j+1<dim_y_)
                    cells_[i+1][j+1].incr_neigh();
                if(i+1<dim_x_)
                    cells_[i+1][j].incr_neigh();
                if(i+1<dim_x_ && j>0)
                    cells_[i+1][j-1].incr_neigh();
            }
        }
    }
    bool get_cell_state(const size_t x, const size_t y)
    {
        return cells_[x][y].get_state();
    }
    void apply_rules(const rules_container rules){
        for(size_t i=0; i<dim_x_; i++){
            for(size_t j=0; j<dim_y_; j++){
                unsigned int nb=cells_[i][j].get_neigh();
                if(cells_[i][j].get_state())
                    cells_[i][j].set_state((rules.survival_min<=nb) && (nb<=rules.survival_max));
                else
                    cells_[i][j].set_state((rules.birth_min<=nb)&& (nb<=rules.birth_max));
                cells_[i][j].reset_neigh();
                }
        }
    }
    void set_cell(size_t i, size_t j, bool state){
        cells_[i][j].set_state(state);
    }
    void stamp_board(Board b, const unsigned int x, const unsigned int y)
    {
        for(size_t i = 0; i<std::min(dim_x_-x, b.get_size_x()); i++)
        {
            for(size_t j = 0; j<std::min(dim_y_-y, b.get_size_y()); j++)
            {
                cells_[i+x][j+y].set_state(b.get_cell_state(i, j));
            }
        }
        
        //std::cout << cells_[2][2].get_state();
    }
    vector<vector<Cell>> get_cells()
    {
        return cells_;
    }
    
};
