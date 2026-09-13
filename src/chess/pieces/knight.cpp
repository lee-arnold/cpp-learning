#include "knight.h"
#include "chess/colour.h"
#include "chess/piece.h"
#include "chess/piece_type.h"

namespace chess {

Knight::Knight(Colour colour)
    : Piece{colour == Colour::White ? "♘" : "♞", colour, PieceType::Knight} {
}

}
