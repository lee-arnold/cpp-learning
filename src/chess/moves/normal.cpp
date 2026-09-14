#include "normal.h"
#include "chess/board.h"
#include "chess/move.h"
#include "chess/move_type.h"
#include "chess/position.h"
#include <memory>
#include <utility>

namespace chess {

Normal::Normal(Position from, Position to) : Move{MoveType::Normal, from, to} {
}

void Normal::execute(Board &board) const {
    board[to()] = std::move(board[from()]);
    // piece.hasMoved = true
}

}
