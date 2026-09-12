#include "pawn.h"

namespace chess {

Pawn::Pawn(Colour colour) : Piece{colour == Colour::White ? "♙" : "♟", colour} {
}

}
