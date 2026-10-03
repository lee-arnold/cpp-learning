#include "chess/pieces/piece.h"
#include "chess/colour.h"
#include "chess/pieces/piece_type.h"

namespace chess {

Piece::Piece(Colour colour, PieceType type) : colour_{colour}, type_{type} {
}

Colour Piece::colour() const {
    return colour_;
}

PieceType Piece::type() const {
    return type_;
}

bool Piece::has_moved() const {
    return has_moved_;
}

void Piece::set_has_moved() {
    has_moved_ = true;
}

}
