#include "moves.h"
#include "chess/board.h"
#include "chess/position.h"
#include <utility>

#include <catch2/catch_test_macros.hpp>

void relocate_piece(
    chess::Board &board, chess::Position from, chess::Position to, bool set_has_moved
) {
    REQUIRE(chess::Board::is_inside(from));
    REQUIRE(chess::Board::is_inside(to));
    REQUIRE(!board.is_empty(from));

    if (from == to) return;

    board[to] = std::move(board[from]);

    if (set_has_moved) board[to]->set_has_moved();
}
