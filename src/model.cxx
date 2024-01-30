#include "model.hxx"
#include "grid.hxx"
#include <iostream>

Model::Model()
        : game_over_(false),
          current_block_(Block(Color::Red, {5, -3}, 3)),
          blocks_(),
          grid_(10, 20),
          score_(0)

{

    generate_nxt_block();
}

Grid& Model::get_grid()
{
    return grid_;
}



int Model::get_score() const
{
    return score_;
}

bool Model::is_game_over() const
{
    return game_over_;
}

void Model::move_block_left()
{

    if (!valid_next_position({-1, 0}))
    {

    }
    else {
        current_block_.move_left();
    }
}

void Model::move_block_right()
{
    if (!valid_next_position({1, 0}))
    {

    }
    else {
        current_block_.move_right();
    }
}

void Model::move_block_down()
{
    // Block next_block = current_block_;

    if (!valid_next_position({0, 1}))
    {
        // current_block_.undo_last_move(); // Undo the invalid move
        if (current_block_.get_top_y() <= 0)
        {
            game_over_ = true; // The block has collided at the top, game over
        }
        else
        {
            std::cout << "HELLO?";
            place_block(); // The block has landed, place it in the grid
            clear_lines(); // Clear complete lines, if any
            generate_nxt_block(); // Generate the next block
        }
    }
    else {
        current_block_.move_down();
    }


}

bool Model::valid_next_position(ge211::Dims<int> direction) {
    for (auto position: current_block_.get_positions()) {
        ge211::Posn<int> next_pos = {position.x + direction.width, position.y
                                     + direction.height};
        if (next_pos.y >= 20 || next_pos.x < 0 || next_pos.x >= 10) {
            return false;
        }

        if (next_pos.y >= 0 && grid_.cells_[next_pos.y][next_pos.x]) {
            return false;
        }

    }
    return true;
}

void Model::rotate_block_clockwise()
{
    current_block_.rotate();
}



void Model::place_block()
{
    grid_.place_block(current_block_);
    blocks_.push_back(current_block_);
    check_game_over();
}

void Model::clear_lines()
{
    int cleared_lines = 0;
    for (int row = 0; row < grid_.height_; ++row) {
        if (grid_.is_row_complete(row)) {
            grid_.clear_row(row);
            ++cleared_lines;
        }
    }
    score_ += cleared_lines * 100;
}

void Model::generate_nxt_block()
{
    ge211::Random_source<int> rand(0,6);

    Block::Position position {5, -3};
    Color color = Color::Magenta;
    int current_shape = rand.next();

    current_block_ = Block(color, position, current_shape);
}


void Model::set_fall_accelerated(bool accelerated)
{
    if (accelerated)
    {
        grid_.set_fall_delay(.1); //Adjust fall delay accelerated falling
    }
    else
    {
        grid_.reset_fall_delay(); // Reset the fall delay to the initial value
    }
}

void Model::reset()
{
    grid_.clear_grid();
    score_ = 0;
    game_over_ = false;
    generate_nxt_block();
}

void Model::check_collision()
{
    if (grid_.has_collision(current_block_))
    {
        current_block_.undo_last_move();

        if (current_block_.get_top_y() <= 0)
        {
            game_over_ = true;
        }
        else
        {
            place_block();
            clear_lines();
            generate_nxt_block();
        }
    }
}


void Model::check_game_over()
{
    if (grid_.is_block_landed(current_block_)
    && current_block_.get_top_y() <= 0)
    {
        game_over_ = true;
        Model::reset();
    }
}
