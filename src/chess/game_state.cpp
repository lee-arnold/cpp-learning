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

std::vector<std::unique_ptr<Move>> GameState::available_moves_for_piece(
    const Position position
) const {
    if (!board_.is_inside(position) ||
        board_.is_empty(position) ||
        board_[position]->colour() != current_player_) {
        return std::vector<std::unique_ptr<Move>>{};
    }

    auto &piece = board_[position];

    // TODO: filter out moves that leave our king in check
    return piece->get_moves(position, board_);
}

void GameState::execute_move(const Move &move) {
    move.execute(board_);
    current_player_ = Player::opponent(current_player_);
}

};
