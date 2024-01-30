#pragma once

#include "model.hxx"
#include <ge211.hxx>
#include <ge211_color.hxx>
#include <vector>
#include <ge211_resource.hxx>

#include "grid.hxx"

class View
{
public:
    using Dimensions = ge211::Dims<int>;
    using Position = ge211::Posn<int>;

    explicit View(Model&);

    void draw(ge211::Sprite_set& set);

    Dimensions initial_window_dimensions() const;
    std::string initial_window_title() const;

private:
    Model& model_;

    // Dimensions and positions of various elements
    static int const block_size = 30;

    static int const grid_size = 36;
    ge211::Rectangle_sprite sprite_grid;
    ge211::Rectangle_sprite light_square;
    ge211::Rectangle_sprite dark_square;
    ge211::Rectangle_sprite test_square;
    ge211::Rectangle_sprite next_block_rect;
    ge211::Text_sprite game_over_text;
    ge211::Text_sprite score_txt;

    Position score_position;
    Position game_over_position;

    Position grid_to_screen(const Position& grid_position) const
    {
        int screen_x = grid_position.x * block_size;
        int screen_y = grid_position.y * block_size;
        return {screen_x, screen_y};
    }

    Dimensions cell_dimensions_;
    ge211::Font font;
};