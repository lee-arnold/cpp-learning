#include "queen.h"
#include "chess/colour.h"
#include "chess/piece.h"

namespace chess {

Queen::Queen(Colour colour) : Piece{colour == Colour::White ? "♕" : "♛", colour} {
}

}
