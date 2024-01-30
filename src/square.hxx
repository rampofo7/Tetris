/*#ifndef SQUARE_HXX_INCLUDED
#define SQUARE_HXX_INCLUDED

#include "ge211.hxx"

struct Position
{
    int x;
    int y;
};

class Square
{
public:
    Square(Position position, ge211::Color color, int size);

    Position get_position() const;
    ge211::Color get_color() const;
    int get_size() const;

private:
    Position position_;
    ge211::Color color_;
    int size_;
};

#endif // SQUARE_HXX_INCLUDED8*/