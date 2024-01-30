#ifndef CONTROLLER_HXX_INCLUDED
#define CONTROLLER_HXX_INCLUDED
#include <ge211.hxx>
#include "model.hxx"
#include "view.hxx"

class Controller : public ge211::Abstract_game
{
public:
    explicit Controller();

    void handle_key_up(ge211::Key key);
    void handle_key_down(ge211::Key key);
    void update(double dt);
    void clear_lines();
    bool is_game_over() const;

    void on_frame(double dt) override;
    void on_load();
    void on_key_down(ge211::Key key) override;
    void on_key_up(ge211::Key key) override;
    void draw(ge211::Sprite_set&) override;
    View::Dimensions initial_window_dimensions() const override;
    std::string initial_window_title() const override;

private:
    Model model_;
    View view_;

    static constexpr int grid_width_ = 10;
    static constexpr int grid_height_ = 20;
    static constexpr double initial_fall_delay_ = 1.0;
    double fall_delay_ = 1;
    int fall_counter_;

    double timer = 0;
};

#endif // CONTROLLER_HXX_INCLUDED