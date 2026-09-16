#include "chess/pieces/bishop.h"
#include "chess/colour.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"

namespace chess {

Bishop::Bishop(Colour colour)
    : Piece{colour == Colour::White ? "♗" : "♝", colour, PieceType::Bishop} {
}

}
