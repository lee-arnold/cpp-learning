#include "chess/board.h"
#include "chess/colour.h"
#include "chess/game_state.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include "helpers/moves.h"
#include "helpers/squares.h"

#include <catch2/catch_test_macros.hpp>

#include <algorithm>

using namespace test_squares;

TEST_CASE("An unmoved white pawn with a clear path can advance one or two squares") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    const auto destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 2);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());
}

TEST_CASE("An unmoved black pawn with a clear path can advance one or two squares, or capture") {
    chess::Board board;
    chess::GameState game{chess::Colour::Black, board};

    relocate_piece(board, a2, g6, true);
    const auto destinations = get_destinations_for_piece(game, h7);

    REQUIRE(destinations.size() == 3);
    REQUIRE(std::ranges::find(destinations, h6) != destinations.end());
    REQUIRE(std::ranges::find(destinations, h5) != destinations.end());
    REQUIRE(std::ranges::find(destinations, g6) != destinations.end());
}

TEST_CASE("A previously moved pawn with a clear path can advance only one square") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, a2, a3, true);

    const auto destinations = get_destinations_for_piece(game, a3);

    REQUIRE(destinations.size() == 1);
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());
}

TEST_CASE("A friendly piece immediately ahead prevents all pawn forward moves") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, b2, a3);

    const auto moves = game.available_moves_for_piece(a2);

    REQUIRE(moves.empty());
}

TEST_CASE("An enemy piece immediately ahead prevents all pawn forward moves") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, b7, a3);

    const auto moves = game.available_moves_for_piece(a2);

    REQUIRE(moves.empty());
}

TEST_CASE("A friendly piece two squares ahead allows only the one-square pawn advance") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, b2, a4);
    const auto destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 1);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
}

TEST_CASE("An enemy piece two squares ahead allows only the one-square pawn advance") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, b7, a4);
    const auto destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 1);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
}

TEST_CASE(
    "An unmoved white pawn one rank from the edge has only an in-bounds one-square destination"
) {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    clear_piece(board, a8);
    clear_piece(board, b8);
    relocate_piece(board, a2, a7);
    const auto destinations = get_destinations_for_piece(game, a7);

    REQUIRE(destinations.size() == 1);
    REQUIRE(std::ranges::find(destinations, a8) != destinations.end());
}

TEST_CASE(
    "An unmoved black pawn one rank from the edge has only an in-bounds one-square destination"
) {
    chess::Board board;
    chess::GameState game{chess::Colour::Black, board};

    clear_piece(board, a1);
    clear_piece(board, b1);
    relocate_piece(board, a7, a2);
    const auto destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 1);
    REQUIRE(std::ranges::find(destinations, a1) != destinations.end());
}

TEST_CASE("Moves generated for a pawn start at the pawn's current square") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    const auto source_positions = get_source_positions_for_piece(game, a2);

    REQUIRE(!source_positions.empty());
    REQUIRE(std::ranges::all_of(source_positions, [](const auto &position) {
        return position == a2;
    }));
}

TEST_CASE("Querying pawn moves leaves the pawn and its forward squares unchanged.") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    auto a2_ptr = board[a2].get();
    auto a3_ptr = board[a3].get();
    auto a4_ptr = board[a4].get();

    get_destinations_for_piece(game, a2);

    REQUIRE(a2_ptr == board[a2].get());
    REQUIRE(!a2_ptr->has_moved());
    REQUIRE(a3_ptr == board[a3].get());
    REQUIRE(a4_ptr == board[a4].get());
}

TEST_CASE(
    "Repeated queries on an unchanged board return the same pawn destinations without duplicates"
) {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    auto destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 2);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());

    destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 2);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());

    destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 2);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());
}

TEST_CASE("Querying an empty square returns no available moves") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    const auto moves = game.available_moves_for_piece(a4);

    REQUIRE(moves.empty());
}

TEST_CASE("Querying a position beyond any board edge returns no available moves") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    auto moves = game.available_moves_for_piece(chess::Position{-1, 1});

    REQUIRE(moves.empty());

    moves = game.available_moves_for_piece(chess::Position{1, -1});

    REQUIRE(moves.empty());

    moves = game.available_moves_for_piece(chess::Position{8, 1});

    REQUIRE(moves.empty());

    moves = game.available_moves_for_piece(chess::Position{1, 8});

    REQUIRE(moves.empty());
}

TEST_CASE("A white pawn can capture an enemy piece one square diagonally forward") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, a7, b3);

    const auto destinations = get_destinations_for_piece(game, a2);

    REQUIRE(destinations.size() == 3);
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, b3) != destinations.end());

    const auto moves = game.available_moves_for_piece(a2);

    REQUIRE(!moves.empty());

    auto move = std::ranges::find_if(moves, [](auto &move) { return move->to() == b3; });

    REQUIRE(move != moves.end());

    game.execute_move(**move);

    REQUIRE(!board[a2]);
    REQUIRE(board[b3]->type() == chess::PieceType::Pawn);
    REQUIRE(board[b3]->colour() == chess::Colour::White);
}

TEST_CASE("A white pawn can capture an enemy to its left but not a friendly piece to its right") {
    chess::Board board;
    chess::GameState game{chess::Colour::White, board};

    relocate_piece(board, a2, c3);
    relocate_piece(board, a7, a3);

    const auto destinations = get_destinations_for_piece(game, b2);

    REQUIRE(destinations.size() == 3);
    REQUIRE(std::ranges::find(destinations, b3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, b4) != destinations.end());
    REQUIRE(std::ranges::find(destinations, a3) != destinations.end());
    REQUIRE(std::ranges::find(destinations, c3) == destinations.end());
}
