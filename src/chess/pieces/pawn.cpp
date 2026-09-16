#include "chess/pieces/pawn.h"
#include "chess/colour.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"

namespace chess {

Pawn::Pawn(Colour colour) : Piece{colour == Colour::White ? "♙" : "♟", colour, PieceType::Pawn} {
}

}
