#pragma once
#include "ge211.hxx"
#include <vector>
#include <ge211_sprites.hxx>

enum class Color
{
    Red,
    Green,
    Blue,
    Yellow,
    Cyan,
    Magenta,
    Black,
    White

};

class Block
{
public:
    using Position = ge211::Posn<int>;

    Block(Color color, Position position, int shape);

    void move_left();
    void move_right();
    void move_down();
    void rotate();

    Color get_color() const;
    Position get_position() const;
    ge211::Color gett_color() const;

    // Shapes
    static std::vector<std::vector<bool>> shape_I();
    static std::vector<std::vector<bool>> shape_J();
    static std::vector<std::vector<bool>> shape_L();
    static std::vector<std::vector<bool>> shape_O();
    static std::vector<std::vector<bool>> shape_S();
    static std::vector<std::vector<bool>> shape_T();
    static std::vector<std::vector<bool>> shape_Z();

    std::vector<Position> get_positions() const
    {
        return positions_;
    }

    void undo_last_move();
    int get_top_y() const;

    bool has_value() const {
        return !positions_.empty();
    }

    void update_positions();

    // void
    // move(int i_1);
private:
    Color color_;
    Position position_;
    std::vector<std::vector<std::vector<bool>>> shapes_;
    int shapeIndex_;
    std::vector<Position> positions_;
    ge211::Color colorr_;

};