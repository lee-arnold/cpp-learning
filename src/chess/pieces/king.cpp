#include "king.h"
#include "chess/colour.h"
#include "chess/piece.h"

namespace chess {

King::King(Colour colour) : Piece{colour == Colour::White ? "♔" : "♚", colour} {
}

}
