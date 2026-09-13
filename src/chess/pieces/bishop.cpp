#include "bishop.h"
#include "chess/colour.h"
#include "chess/piece.h"
#include "chess/piece_type.h"

namespace chess {

Bishop::Bishop(Colour colour)
    : Piece{colour == Colour::White ? "♗" : "♝", colour, PieceType::Bishop} {
}

}
