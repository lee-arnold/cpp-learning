#include "chess/moves/normal.h"
#include "chess/board.h"
#include "chess/moves/move.h"
#include "chess/moves/move_type.h"
#include "chess/position.h"
#include <memory>
#include <utility>

namespace chess {

NormalMove::NormalMove(Position from, Position to) : Move{MoveType::Normal, from, to} {
}

void NormalMove::execute(Board &board) const {
    board[to()] = std::move(board[from()]);
    // piece.hasMoved = true
}

}
