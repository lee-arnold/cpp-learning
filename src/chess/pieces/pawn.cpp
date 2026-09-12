#include "pawn.h"
#include "chess/colour.h"
#include "chess/piece.h"

namespace chess {

Pawn::Pawn(Colour colour) : Piece{colour == Colour::White ? "♙" : "♟", colour} {
}

}
