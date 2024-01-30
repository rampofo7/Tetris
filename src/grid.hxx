#pragma once

#include "ge211.hxx"
#include "block.hxx"
#include <vector>


class Grid
{
public:
    static const int rows = 20;
    static const int cols = 10;

    Grid(int grid_width, int grid_height);

    // bool is_valid_posit/**/ion(const Block& block) const;
    bool is_row_complete(int row) const;
    void clear_row(int row);
    bool is_game_over() const;

    void place_block(const Block& block);
    void update();
    // bool is_color_empty(const ge211::Color& color) const;
    int width_;
    int height_;
    bool is_block_landed(const Block& block) const;
    void set_fall_delay(double delay);
    void clear_grid();
    void reset_fall_delay();
    bool has_collision(const Block& block) const;
    void set_color_empty(int row, int col);
    double fall_delay_;
    int get_width() const { return width_; }
    int get_height() const { return height_; }
    std::vector<std::vector<bool>> cells_;



private:

    bool game_over_;


};