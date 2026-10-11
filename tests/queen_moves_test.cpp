#include "chess/board.h"
#include "chess/game_state.h"
#include "helpers/moves.h"
#include "helpers/squares.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>

using namespace test_squares;

TEST_CASE("A queen in the centre generates moves in all eight directions and respects blockers") {
    chess::Board board;
    const chess::GameState game{board};

    relocate_piece(board, d1, d4);
    clear_piece(board, g1);

    const auto destinations = get_destinations_for_piece(game, d4);

    REQUIRE(destinations.size() == 19);

    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a7) != destinations.end());

    REQUIRE(std::ranges::find(destinations, b4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, b6) != destinations.end());

    REQUIRE(std::ranges::find(destinations, c4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, c3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, c5) != destinations.end());

    REQUIRE(std::ranges::find(destinations, d3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, d5) != destinations.end());
    REQUIRE(std::ranges::find(destinations, d6) != destinations.end());
    REQUIRE(std::ranges::find(destinations, d7) != destinations.end());

    REQUIRE(std::ranges::find(destinations, e4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, e5) != destinations.end());

    REQUIRE(std::ranges::find(destinations, f4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, f6) != destinations.end());

    REQUIRE(std::ranges::find(destinations, g4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, g7) != destinations.end());

    REQUIRE(std::ranges::find(destinations, h4) != destinations.end());
}
