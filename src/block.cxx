#include "block.hxx"
#include <iostream>

// ge211::Random_source<int> rand(0,6);
// int shape = rand.next();
// Block(..., ..., shape)
Block::Block(Color color, Position position, int shape = 0)
        : color_(color),
          position_(position),
          shapes_({shape_I(), shape_J(), shape_L(),  shape_O(), shape_S(),
                   shape_T(), shape_Z()}),
          shapeIndex_(shape)

{
    std::cout << position_;
    std::vector<std::vector<bool>> selectedShape = shapes_[shapeIndex_];

    for (std::size_t row = 0; row < selectedShape.size(); ++row) {
        for (std::size_t col = 0; col < selectedShape[row].size(); ++col) {
            if (selectedShape[row][col]) {
                positions_.push_back(position_.right_by(col).down_by(row));
            }
        }
    }
}

void Block::move_left()
{
    position_.x-=1;
    update_positions();
}

void Block::move_right()
{
    position_.x+=1;
    update_positions();
}

void Block::move_down()
{
    position_.y+=1;
    update_positions();

}

void Block::update_positions() {
    positions_.clear();
    std::vector<std::vector<bool>> selectedShape = shapes_[shapeIndex_];

    for (std::size_t row = 0; row < selectedShape.size(); ++row) {
        for (std::size_t col = 0; col < selectedShape[row].size(); ++col) {
            if (selectedShape[row][col]) {
                positions_.push_back(position_.right_by(col).down_by(row));
            }
        }
    }
}

void Block::rotate()
{
    // Retrieve the current shape of the block
    std::vector<std::vector<bool>> currentShape;

    // Determine which shape to use based on shapeIndex_
    switch (shapeIndex_)
    {
    case 0:
        currentShape = shape_I();
        break;
    case 1:
        currentShape = shape_J();
        break;
    case 2:
        currentShape = shape_L();
        break;
    case 3:
        currentShape = shape_O();
        break;
    case 4:
        currentShape = shape_S();
        break;
    case 5:
        currentShape = shape_T();
        break;
    case 6:
        currentShape = shape_Z();
        break;
    default:
        // Invalid shape index
        return;
    }

    // Calculate the dimensions of the current shape
    int rows = currentShape.size();
    int cols = currentShape[0].size();

    // Create a new shape to store the rotated block
    std::vector<std::vector<bool>> rotatedShape
    (cols,std::vector<bool>(rows));

    // Perform the rotation
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            rotatedShape[j][rows - i - 1] = currentShape[i][j];
        }
    }

    // Update the block's shape with the rotated shape
    switch (shapeIndex_)
    {
    case 0:
        shapes_[0] = std::move(rotatedShape);
        break;
    case 1:
        shapes_[1] = std::move(rotatedShape);
        break;
    case 2:
        shapes_[2] = std::move(rotatedShape);
        break;
    case 3:
        shapes_[3] = std::move(rotatedShape);
        break;
    case 4:
        shapes_[4] = std::move(rotatedShape);
        break;
    case 5:
        shapes_[5] = std::move(rotatedShape);
        break;
    case 6:
        shapes_[6] = std::move(rotatedShape);
        break;
    }
}

Color Block::get_color() const
{
    return color_;
}

ge211::Color Block::gett_color() const
{
    return colorr_;
}

Block::Position Block::get_position() const
{
    return position_;
}

// Shapes

std::vector<std::vector<bool>> Block::shape_I()
{
    return {{true, true, true, true}};
}

std::vector<std::vector<bool>> Block::shape_J()
{
    return {
            {true, false, false},
            {true, true, true}
    };
}

std::vector<std::vector<bool>> Block::shape_L()
{
    return {
            {false, false, true},
            {true, true, true}
    };
}

std::vector<std::vector<bool>> Block::shape_O()
{
    return {
            {true, true},
            {true, true}
    };
}

std::vector<std::vector<bool>> Block::shape_S()
{
    return {
            {false, true, true},
            {true, true, false}
    };
}

std::vector<std::vector<bool>> Block::shape_T()
{
    return {
            {false, true, false},
            {true, true, true}
    };
}

std::vector<std::vector<bool>> Block::shape_Z()
{
    return {
            {true, true, false},
            {false, true, true}
    };
}

void Block::undo_last_move()
{
    // Decrement the position of the block by one in the y-direction
    position_.y -= 1;
}

int Block::get_top_y() const
{
    int top_y = position_.y;
    for (const auto& position : positions_)
    {
        int y = position.y + position_.y;
        if (y < top_y)
            top_y = y;
    }
    return top_y;
}


