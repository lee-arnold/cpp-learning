#include "queen.h"

namespace chess {

Queen::Queen(Colour colour) : Piece{colour == Colour::White ? "♕" : "♛", colour} {
}

}
