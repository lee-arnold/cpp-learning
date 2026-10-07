#include "moves.h"
#include "chess/board.h"
#include "chess/game_state.h"
#include "chess/position.h"

#include <catch2/catch_test_macros.hpp>

#include <utility>
#include <vector>

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

std::vector<chess::Position> get_destinations_for_piece(
    const chess::GameState &game, const chess::Position from
) {
    const auto moves = game.available_moves_for_piece(from);

    std::vector<chess::Position> destinations;
    for (const auto &move : moves) {
        destinations.push_back(move->to());
    }

    return destinations;
}

void clear_piece(chess::Board &board, chess::Position position) {
    REQUIRE(chess::Board::is_inside(position));
    REQUIRE(!board.is_empty(position));
    board[position] = nullptr;
}
