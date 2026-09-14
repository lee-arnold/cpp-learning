#include "move.h"
#include "chess/move_type.h"
#include "chess/position.h"

namespace chess {

Move::Move(MoveType type, Position from, Position to) : type_{type}, from_{from}, to_{to} {
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

bool Move::is_legal() const {
    return false;
}

}
