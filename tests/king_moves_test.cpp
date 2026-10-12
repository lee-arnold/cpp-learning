#include "chess/board.h"
#include "chess/colour.h"
#include "chess/game_state.h"
#include "helpers/moves.h"
#include "helpers/squares.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>

using namespace test_squares;

TEST_CASE(
    "A king with empty surrounding squares can move exactly one square in all eight directions"
) {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, e1, d4);

    const auto destinations = get_destinations_for_piece(game, d4);

    REQUIRE(destinations.size() == 8);
    REQUIRE(std::ranges::find(destinations, c3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, c4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, c5) != destinations.end());
    REQUIRE(std::ranges::find(destinations, d3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, d5) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e5) != destinations.end());
}

TEST_CASE("A king can capture adjacent enemy pieces but cannot move onto friendly pieces") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, d7, e2);

    const auto destinations = get_destinations_for_piece(game, e1);

    REQUIRE(destinations.size() == 1);
    REQUIRE(std::ranges::find(destinations, e2) != destinations.end());
}

TEST_CASE("A king in a corner with empty surrounding squares has exactly three destinations") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, e1, a1);
    clear_piece(board, a2);
    clear_piece(board, b1);
    clear_piece(board, b2);

    const auto destinations = get_destinations_for_piece(game, a1);

    REQUIRE(destinations.size() == 3);
    REQUIRE(std::ranges::find(destinations, a2) != destinations.end());
    REQUIRE(std::ranges::find(destinations, b1) != destinations.end());
    REQUIRE(std::ranges::find(destinations, b2) != destinations.end());
}
