#include "chess/board.h"
#include "chess/colour.h"
#include "chess/game_state.h"
#include "helpers/moves.h"
#include "helpers/squares.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>

using namespace test_squares;

TEST_CASE("A new game allows White’s moves but not Black’s moves") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    const auto black_destinations = get_destinations_for_piece(game, a7);

    REQUIRE(black_destinations.empty());

    const auto white_destinations = get_destinations_for_piece(game, a2);

    REQUIRE(std::ranges::find(white_destinations, a3) != white_destinations.end());
    REQUIRE(std::ranges::find(white_destinations, a4) != white_destinations.end());
}

TEST_CASE("Executing White and Black moves alternates the current player") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    auto moves = game.available_moves_for_piece(a2);

    REQUIRE(!moves.empty());

    auto &move = moves.front();

    game.execute_move(*move);

    REQUIRE(!board[move->from()]);
    REQUIRE(board[move->to()]);

    REQUIRE(game.current_player() == chess::Colour::Black);

    const auto black_destinations = get_destinations_for_piece(game, a7);

    REQUIRE(std::ranges::find(black_destinations, a5) != black_destinations.end());
    REQUIRE(std::ranges::find(black_destinations, a6) != black_destinations.end());

    const auto white_destinations = get_destinations_for_piece(game, b2);

    REQUIRE(white_destinations.empty());

    moves = game.available_moves_for_piece(a7);

    REQUIRE(!moves.empty());

    game.execute_move(*moves.front());

    REQUIRE(game.current_player() == chess::Colour::White);
}
