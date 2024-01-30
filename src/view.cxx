#include "view.hxx"
#include "grid.hxx"

// Convenient type aliases:
using Colour = ge211::Color;
using Sprite_set = ge211::Sprite_set;


View::View(Model& model)
        : model_(model),
          sprite_grid({grid_size - 7, grid_size - 7}, Colour::medium_magenta
          ()),
          light_square({grid_size - 7, grid_size - 7}, Colour::medium_green
          ()),
          dark_square({grid_size -7, grid_size -7}, Colour::medium_cyan()),
          test_square({grid_size -7, grid_size -7}, Colour::medium_cyan()),
          next_block_rect({block_size * 4, block_size * 4},
                          Colour::medium_green()),
          score_position{model_.get_grid().get_width() * grid_size + 1,
                         20},
          game_over_position{model_.get_grid().get_width() * grid_size / 4 -
          60,  model_.get_grid().get_height() *
          grid_size / 3 - 10},
          cell_dimensions_({30, 30}),
          font("sans.ttf", 30)



{}

void View::draw(Sprite_set& set)
{
    // Draw the grid
    for (int row = 0; row < model_.get_grid().get_height(); ++row) {
        for (int col = 0; col < model_.get_grid().get_width(); ++col) {
            Position pos {col, row};
            if (!model_.get_grid().cells_[row][col]) {
                set.add_sprite(sprite_grid,
                               grid_to_screen(pos), 0);
            }
            else {
                set.add_sprite(dark_square, grid_to_screen(pos), 0);
            }
        }
    }

    Position screen_pos = View::Position{0, 0};
    Dimensions cell_dimensions = {30, 30};
    ge211::Color square_color = {0, 0, 255};
    ge211::Rectangle_sprite rect_sprite = ge211::Rectangle_sprite
            (cell_dimensions,
             square_color);


    for (Block::Position pos: model_.current_block_.get_positions()) {
        if (pos.x < 0 || pos.y < 0) {
            continue;
        }
        screen_pos = grid_to_screen(View::
                                    Position {pos.x, pos.y});
        set.add_sprite(dark_square, screen_pos, 1);

    }

    if (model_.is_game_over()) {
        ge211::Text_sprite::Builder text_builder1(font);
        text_builder1 << "Game Over Bruh.";
        game_over_text.reconfigure(text_builder1);
        set.add_sprite(game_over_text, game_over_position, 100);
    }

     ge211::Text_sprite::Builder text_builder(font);
     text_builder << model_.get_score();
     score_txt.reconfigure(text_builder);
     set.add_sprite(score_txt, score_position, 3);
 }


View::Dimensions View::initial_window_dimensions() const
{
    int window_width = model_.get_grid().get_width() * grid_size + 100;
    int window_height = model_.get_grid().get_height() * grid_size;
    return {window_width, window_height};
}

std::string View::initial_window_title() const
{
    return "Tetris";
}