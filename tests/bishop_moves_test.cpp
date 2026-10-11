#include "chess/board.h"
#include "chess/game_state.h"
#include "helpers/moves.h"
#include "helpers/squares.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>

using namespace test_squares;

TEST_CASE("A bishop can move on all four diagonals and respects blockers") {
    chess::Board board;
    const chess::GameState game{board};

    relocate_piece(board, c1, c5);
    clear_piece(board, g1);

    const auto destinations = get_destinations_for_piece(game, c5);

    REQUIRE(destinations.size() == 8);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a7) != destinations.end());
    REQUIRE(std::ranges::find(destinations, b4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, b6) != destinations.end());
    REQUIRE(std::ranges::find(destinations, d4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, d6) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e7) != destinations.end());
}

TEST_CASE("A bishop in a corner generates only destinations inside the board") {
    chess::Board board;
    const chess::GameState game{board};

    clear_piece(board, a1);
    clear_piece(board, b2);
    relocate_piece(board, c1, a1);

    const auto destinations = get_destinations_for_piece(game, a1);

    REQUIRE(destinations.size() == 6);
    REQUIRE(std::ranges::find(destinations, b2) != destinations.end());
    REQUIRE(std::ranges::find(destinations, c3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, d4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e5) != destinations.end());
    REQUIRE(std::ranges::find(destinations, f6) != destinations.end());
    REQUIRE(std::ranges::find(destinations, g7) != destinations.end());
}
