#include "chess/board.h"
#include "chess/game_state.h"
#include "helpers/moves.h"
#include "helpers/squares.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>

using namespace test_squares;

TEST_CASE("A knight in the centre with empty destination squares has all eight L-shaped moves") {
    chess::Board board;
    const chess::GameState game{board};

    relocate_piece(board, b1, d4);
    clear_piece(board, c2);
    clear_piece(board, e2);

    const auto destinations = get_destinations_for_piece(game, d4);

    REQUIRE(destinations.size() == 8);
    REQUIRE(std::ranges::find(destinations, c2) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e2) != destinations.end());

    REQUIRE(std::ranges::find(destinations, b3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, f3) != destinations.end());

    REQUIRE(std::ranges::find(destinations, b5) != destinations.end());
    REQUIRE(std::ranges::find(destinations, f5) != destinations.end());

    REQUIRE(std::ranges::find(destinations, c6) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e6) != destinations.end());
}

TEST_CASE("A knight can capture an enemy piece on an L-shaped destination square") {
    chess::Board board;
    const chess::GameState game{board};

    relocate_piece(board, b1, d5);

    const auto destinations = get_destinations_for_piece(game, d5);

    REQUIRE(destinations.size() == 8);
    REQUIRE(std::ranges::find(destinations, c3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e3) != destinations.end());

    REQUIRE(std::ranges::find(destinations, b4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, f4) != destinations.end());

    REQUIRE(std::ranges::find(destinations, b6) != destinations.end());
    REQUIRE(std::ranges::find(destinations, f6) != destinations.end());

    REQUIRE(std::ranges::find(destinations, c7) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e7) != destinations.end());
}

TEST_CASE("A knight in the centre generates moves and cannot land on friendly pieces") {
    chess::Board board;
    const chess::GameState game{board};

    relocate_piece(board, b1, d4);

    const auto destinations = get_destinations_for_piece(game, d4);

    REQUIRE(destinations.size() == 6);
    REQUIRE(std::ranges::find(destinations, b3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, f3) != destinations.end());

    REQUIRE(std::ranges::find(destinations, b5) != destinations.end());
    REQUIRE(std::ranges::find(destinations, f5) != destinations.end());

    REQUIRE(std::ranges::find(destinations, c6) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e6) != destinations.end());
}

TEST_CASE("A knight in a corner generates only destinations inside the board") {
    chess::Board board;
    const chess::GameState game{board};

    clear_piece(board, c2);
    relocate_piece(board, b1, a1);

    const auto destinations = get_destinations_for_piece(game, a1);

    REQUIRE(destinations.size() == 2);
    REQUIRE(std::ranges::find(destinations, c2) != destinations.end());
    REQUIRE(std::ranges::find(destinations, b3) != destinations.end());
}
