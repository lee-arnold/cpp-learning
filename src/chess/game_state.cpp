#include "chess/game_state.h"
#include "chess/board.h"
#include "chess/moves/move.h"
#include "chess/position.h"
#include <memory>
#include <vector>

namespace chess {

GameState::GameState(const Board &board) : board_{board} {
}

std::vector<std::unique_ptr<Move>> GameState::legal_moves_for_piece(const Position position) {
    if (board_.is_empty(position)) return std::vector<std::unique_ptr<Move>>{};

    auto &piece = board_[position];

    // filter illegal moves here later
    return piece->get_moves(position, board_);
}

};
