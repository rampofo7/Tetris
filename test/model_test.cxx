#include "model.hxx"
#include <catch.hxx>

TEST_CASE("example test (TODO: replace this)")
{
    CHECK(1 + 1 == 2);
}

//call move_block_down() multiple times until it hits the bottom and stops:
TEST_CASE("Block stops at the bottom")
{
    Model model_;


    model_.current_block_ = Block(Color::Red, {0, 0}, 0);

    for (int i = 0; i < 30; i++)
    {
        model_.move_block_down();
    }

    for (int i = 0; i < 4; i++) {
        CHECK(model_.get_grid().cells_[19][i]);
    }

}
//check clear lines, if a row is compelte then clear the line(s) and then
// bottom row should not be complete and the score should be > 0
TEST_CASE("Clear lines")
{
    Model model_;
    for (int col = 0; col < 10; ++col) {
        model_.get_grid().cells_[19][col] = true;
    }

    CHECK(model_.get_grid().is_row_complete(19) == true);
    model_.clear_lines();


    CHECK(model_.get_grid().is_row_complete(19) == false);


    CHECK(model_.get_score() > 0);
}

//check that starting score is always zero
TEST_CASE("Initial score is zero")
{
    Model model_;
    CHECK(model_.get_score() == 0);
}

TEST_CASE("Clear multiple lines")
{
    Model model_;

    // Manually set multiple complete lines in the grid
    for (int row = 17; row <= 19; ++row) {
        for (int col = 0; col < 10; ++col) {
            model_.get_grid().cells_[row][col] = true;
        }
    }

    // Save the initial score
    int initial_score = model_.get_score();

    // Call the clear_lines() method
    model_.clear_lines();

    // Assert that the lines have been cleared
    for (int row = 17; row <= 19; ++row) {
        for (int col = 0; col < 10; ++col) {
            CHECK_FALSE(model_.get_grid().cells_[row][col]);
        }
    }

    // Assert that the score has been updated accordingly
    CHECK(model_.get_score() > initial_score);
}

//simulate moving block up by repeatedly calling move_block_down()
// until game over condition is triggered when block collides with the top
TEST_CASE("Game over when block collides at top")
{
    Model model_;

    while (!model_.is_game_over()) {
        model_.move_block_down();
    }

    CHECK(model_.is_game_over());

}

// Move the block to the right until it collides with the right boundary
// make sure it doesn't go past
TEST_CASE("Block collision Right boundary")
{
    Model model_;

    model_.current_block_ = Block(Color::Red, {5, 0}, 0);
    model_.current_block_.rotate();

    while (true) {
        bool found = false;
        for (auto position : model_.current_block_.get_positions()) {
            if (position.x == 9) {
                found = true;
                break;
            }

        }
        if (found) {
            break;
        }
        model_.move_block_right();
    }
    const Block& block = model_.current_block_;
    for (auto position : block.get_positions()) {
        int x = position.x;
        // int y = position.y;
        CHECK(x == 9);

    }
}