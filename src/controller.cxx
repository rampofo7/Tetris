#include "controller.hxx"
#include "view.hxx"

Controller::Controller()
        : model_(),
          view_(model_)
          // font_("sans.ttf", 16)
{}

void Controller::handle_key_up(ge211::Key key)
{
    // Handle key release events
    if (key == ge211::Key::code(' '))
    {
        model_.set_fall_accelerated(false);
    }
}

void Controller::handle_key_down(ge211::Key key)
{
    // Handle key press events
    if (key == ge211::Key::left())
    {
        model_.move_block_left();
    }
    else if (key == ge211::Key::right())
    {
        model_.move_block_right();
    }
    else if (key == ge211::Key::down())
    {
        model_.move_block_down();
        model_.move_block_down();
        // model_.set_fall_accelerated(true);
    }
    else if (key == ge211::Key::up()){
        model_.rotate_block_clockwise();
    }
}

void Controller::update(double dt)
{
    // Update the game state

    if (!model_.is_game_over())
    {
        timer += dt;
        if (timer > fall_delay_) {
            model_.move_block_down();
            timer = 0;
        }

    }
}


void Controller::clear_lines()
{
    // Clear complete lines in the grid
    model_.clear_lines();
}

bool Controller::is_game_over() const
{
    // Check if the game is over
    return model_.is_game_over();
}

void Controller::on_key_down(ge211::Key key)
{

    handle_key_down(key);
}

void Controller::on_frame(double dt)
{
    // Update the game state
    update(dt);
}

void Controller::on_load()
{
    fall_delay_ = initial_fall_delay_;
    fall_counter_ = 0;
}


void Controller::on_key_up(ge211::Key key)
{

    handle_key_up(key);
}

void
Controller::draw(ge211::Sprite_set& sprites)
{
    view_.draw(sprites);
}

View::Dimensions
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

std::string
Controller::initial_window_title() const
{
    return view_.initial_window_title();
}

