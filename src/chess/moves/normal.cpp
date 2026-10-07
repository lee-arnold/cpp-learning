#include "chess/moves/normal.h"
#include "chess/board.h"
#include "chess/moves/move.h"
#include "chess/moves/move_type.h"
#include "chess/position.h"
#include <utility>

namespace chess {

NormalMove::NormalMove(Position from, Position to) : Move{MoveType::Normal, from, to} {
}

void NormalMove::execute(Board &board) const {
    auto &piece = board[from()];

    piece->set_has_moved();
    board[to()] = std::move(board[from()]);
}

}
