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

}
