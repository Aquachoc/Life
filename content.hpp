#include <vector>
#include <iostream>

using std::vector;


typedef struct{
    unsigned int survival_min=2;
    unsigned int survival_max=3;
    unsigned int birth_min=3;
    unsigned int birth_max=8;
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
   // void set_future(bool s){future_state_ = s;};

    unsigned int get_neigh(){return nb_neigh_alive_;};
    bool get_state(){return state_;};
    //int get_future(){return future_state_;};

};

class Board{
private:
    unsigned int nb_turn_;
    unsigned int dim_;
    vector<vector<Cell>> cells_;
public:
    Board(){};
    Board(vector<vector<Cell>>& v){
        cells_=v;
        dim_=v.size();
        };
    vector<vector<bool>> get_board()
    {
        vector<bool> line;
        vector<vector<bool>> arr;
        for(size_t i=0; i<dim_; i++)
        {
            for(size_t j=0; j<dim_; j++)
            {
                line.push_back(cells_[i][j].get_state());
            }
            arr.push_back(line);
            line.clear();
        }
        return arr;
    }
    void init_board(){
        for(size_t i=0; i<dim_; i++){
            for(size_t j=0; j<dim_; j++){
                if(!(cells_[i][j].get_state()))
                    continue;
                if(i>0 && j>0)
                    cells_[i-1][j-1].incr_neigh();
                if(i>0)
                    cells_[i-1][j].incr_neigh();
                if(i>0 && j+1<dim_)
                    cells_[i-1][j+1].incr_neigh();
                if(j>0)
                    cells_[i][j-1].incr_neigh();
                if(j+1<dim_)
                    cells_[i][j+1].incr_neigh();
                if(i+1<dim_ && j+1<dim_)
                    cells_[i+1][j+1].incr_neigh();
                if(i+1<dim_)
                    cells_[i+1][j].incr_neigh();
                if(i+1<dim_ && j>0)
                    cells_[i+1][j-1].incr_neigh();
            }
        }
    }
    void apply_rules(const rules_container rules){
        for(size_t i=0; i<dim_; i++){
            for(size_t j=0; j<dim_; j++){
                unsigned int nb=cells_[i][j].get_neigh();
                if(cells_[i][j].get_state())
                    cells_[i][j].set_state((rules.survival_min<=nb) && (nb<=rules.survival_max));
                else
                    cells_[i][j].set_state((rules.birth_min<=nb)&& (nb<=rules.birth_max));
                //std::cout << nb << std::endl;
                cells_[i][j].reset_neigh();
                }
        }
    }

};




