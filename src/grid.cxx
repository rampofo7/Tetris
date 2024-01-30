#include "grid.hxx"
#include <iostream>

Grid::Grid(int grid_width, int grid_height)
        : width_(grid_width),
          height_(grid_height),
          cells_(rows, std::vector<bool>(cols, false)),
          game_over_(false)

{ }

// bool Grid::is_valid_position(const Block& block) const
// {
//     for (const auto& position : block.get_positions())
//     {
//         int x = block.get_position().x + position.x;
//         int y = block.get_position().y + position.y;
//
//     }
//
//     return true;
// }


bool Grid::is_row_complete(int row) const
{
    for (int x = 0; x < cols; ++x)
    {
        if (!cells_[row][x])
            return false;
    }

    return true;
}

void Grid::clear_row(int row)
{
    // Shift down all the rows above the given row
    for (int y = row; y > 0; --y)
    {
        for (int x = 0; x < cols; ++x)
        {
            cells_[y][x] = cells_[y - 1][x];
        }
    }

    // Clear the top row
    for (int x = 0; x < cols; ++x)
    {
        cells_[0][x] = false;
    }
}

bool Grid::is_game_over() const
{
    return game_over_;
}

void Grid::place_block(const Block& block)
{
    std::cout << "CALLED!!";
    // Get the position and color of the block
    // Block::Position position = block.get_position();
    // Color color = block.get_color();

    // Update the corresponding cells in the grid with the block's color
    for (const auto& blockPosition : block.get_positions())
    {
        int x = blockPosition.x;
        int y = blockPosition.y;
        cells_[y][x] = true;
    }
}

void Grid::update()
{
    // Check if any row is complete
    for (int y = rows - 1; y >= 0; --y)
    {
        if (is_row_complete(y))
        {
            // Clear the complete row
            clear_row(y);
        }
    }
}

bool Grid::is_block_landed(const Block& block) const
{
    // Check if any of the cells occupied by the block are at the bottom of grid
    for (const auto& position : block.get_positions()) {
        int row = position.y;
        if (row == height_ - 1 || cells_[row + 1][position.x]) {
            return true;
        }
    }

    return false;  // Block has not landed
}

void Grid::set_fall_delay(double delay)
{
    fall_delay_ = delay;
}

void Grid::reset_fall_delay()
{
    fall_delay_ = 1.0;
}

bool Grid::has_collision(const Block& block) const
{
    for (const auto& position : block.get_positions())
    {
        int x = position.x;
        int y = position.y;

        if (x < 0 || x >= cols || y < 0 || y >= rows || (cells_[y][x]))
        {
            return true; // Collision detected
        }
    }

    return false; // No collision
}

void Grid::clear_grid()
{
    // Clear all cells in the grid
    for (int row = 0; row < height_; ++row) {
        for (int col = 0; col < width_; ++col) {
            set_color_empty(row, col);
        }
    }
}

void Grid::set_color_empty(int row, int col)
{
    cells_[row][col] = false;
}