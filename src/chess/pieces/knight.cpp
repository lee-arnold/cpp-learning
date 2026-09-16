#include "chess/pieces/knight.h"
#include "chess/colour.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"

namespace chess {

Knight::Knight(Colour colour)
    : Piece{colour == Colour::White ? "♘" : "♞", colour, PieceType::Knight} {
}

}
