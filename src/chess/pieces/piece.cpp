#include "chess/pieces/piece.h"
#include "chess/colour.h"
#include "chess/pieces/piece_type.h"

#include <string_view>

namespace chess {

Piece::Piece(std::string_view icon, Colour colour, PieceType type)
    : icon_{icon}, colour_{colour}, type_{type} {
}

std::string_view Piece::icon() const {
    return icon_;
}

Colour Piece::colour() const {
    return colour_;
}

PieceType Piece::type() const {
    return type_;
}

}
