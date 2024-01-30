#ifndef MODEL_HXX_INCLUDED
#define MODEL_HXX_INCLUDED

#include <ge211.hxx>
#include "grid.hxx"
#include "block.hxx"

class Model
{
public:
    Model();
    Grid& get_grid();
    int get_score() const;
    bool is_game_over() const;
    void move_block_left();
    void move_block_right();
    void move_block_down();
    void rotate_block_clockwise();
    void place_block();
    void clear_lines();
    void set_fall_accelerated(bool accelerated);
    void generate_nxt_block();
    bool game_over_;
    Block current_block_;
    std::vector<Block> blocks_;
    bool valid_next_position(ge211::Dims<int> direction);
private:
    Grid grid_;
    int score_;
    void reset();
    void check_collision();
    void check_game_over();
};

#endif // MODEL_HXX_INCLUDED