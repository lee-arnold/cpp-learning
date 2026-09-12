#include "king.h"

namespace chess {

King::King(Colour colour) : Piece{colour == Colour::White ? "♔" : "♚", colour} {
}

}
