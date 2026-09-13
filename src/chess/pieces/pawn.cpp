#include "pawn.h"
#include "chess/colour.h"
#include "chess/piece.h"
#include "chess/piece_type.h"

namespace chess {

Pawn::Pawn(Colour colour) : Piece{colour == Colour::White ? "♙" : "♟", colour, PieceType::Pawn} {
}

}
