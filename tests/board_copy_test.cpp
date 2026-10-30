#include "chess/board.h"
#include "chess/colour.h"
#include "chess/game_state.h"
#include "chess/moves/move.h"
#include "chess/moves/normal.h"
#include "chess/pieces/piece.h"
#include "chess/position.h"
#include "helpers/moves.h"
#include "helpers/squares.h"
#include <catch2/catch_test_macros.hpp>
#include <memory>
#include <typeinfo>

using namespace test_squares;

TEST_CASE("A board copy preserves all squares and piece state with independent ownership") {
    chess::Board board;
    relocate_piece(board, a2, a4, true);
    relocate_piece(board, b8, c6, true);
    auto copy = board.copy();

    for (int rank = 0; rank < board.dimension(); ++rank) {
        for (int file = 0; file < board.dimension(); ++file) {
            const auto position = chess::Position{rank, file};

            REQUIRE(copy.is_empty(position) == board.is_empty(position));

            if (board.is_empty(position)) continue;

            REQUIRE(copy[position].get() != board[position].get());
            REQUIRE(copy[position]->type() == board[position]->type());
            REQUIRE(copy[position]->colour() == board[position]->colour());
            REQUIRE(copy[position]->has_moved() == board[position]->has_moved());

            const auto *copied_piece = copy[position].get();
            const auto *original_piece = board[position].get();

            REQUIRE(typeid(*copied_piece) == typeid(*original_piece));
        }
    }

    const auto *original_pawn = board[b2].get();
    const auto move = chess::NormalMove{b2, b3};

    move.execute(copy);

    REQUIRE(copy.is_empty(b2));
    REQUIRE(copy[b3]->has_moved());
    REQUIRE(board[b2].get() == original_pawn);
    REQUIRE_FALSE(board[b2]->has_moved());
    REQUIRE(board.is_empty(b3));

    copy[a8] = nullptr;

    REQUIRE(board[a8]);
}

TEST_CASE("Legal move queries leave the original board and turn unchanged") {
    chess::Board board;
    const auto snapshot = board.copy();
    chess::GameState game{chess::Colour::White, board};

    REQUIRE_FALSE(game.available_moves_for_piece(e2).empty());
    REQUIRE(game.current_player() == chess::Colour::White);

    for (int rank = 0; rank < board.dimension(); ++rank) {
        for (int file = 0; file < board.dimension(); ++file) {
            const auto position = chess::Position{rank, file};

            REQUIRE(board.is_empty(position) == snapshot.is_empty(position));

            if (board.is_empty(position)) continue;

            REQUIRE(board[position]->type() == snapshot[position]->type());
            REQUIRE(board[position]->colour() == snapshot[position]->colour());
            REQUIRE(board[position]->has_moved() == snapshot[position]->has_moved());
        }
    }
}
