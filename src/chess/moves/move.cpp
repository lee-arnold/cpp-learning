#include "chess/moves/move.h"
#include "chess/board.h"
#include "chess/moves/move_type.h"
#include "chess/position.h"

namespace chess {

Move::Move(MoveType type, Position from, Position to)
    : type_{type},
      from_{from},
      to_{to} {
}

Position Move::from() const {
    return from_;
}

Position Move::to() const {
    return to_;
}

MoveType Move::type() const {
    return type_;
}

bool Move::is_legal(const Board &board) const {
    auto player = board[from()]->colour();
    auto copy = board.copy();
    execute(copy);
    return !copy.is_in_check(player);
}

}
