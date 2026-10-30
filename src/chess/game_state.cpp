#include "chess/game_state.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/moves/move.h"
#include "chess/player.h"
#include "chess/position.h"
#include <memory>
#include <vector>

namespace chess {

GameState::GameState(Colour player, Board &board)
    : board_{board},
      current_player_{player} {
}

Colour GameState::current_player() const {
    return current_player_;
}

std::vector<std::unique_ptr<Move>> GameState::available_moves_for_piece(Position position) const {
    if (!board_.is_inside(position) ||
        board_.is_empty(position) ||
        board_[position]->colour() != current_player_) {
        return std::vector<std::unique_ptr<Move>>{};
    }

    auto &piece = board_[position];
    auto moves = piece->get_moves(position, board_);

    std::erase_if(moves, [this](auto &move) { return !move->is_legal(board_); });

    return moves;
}

void GameState::execute_move(const Move &move) {
    move.execute(board_);
    current_player_ = opponent(current_player_);
}

};
