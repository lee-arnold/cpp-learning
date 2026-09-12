#include "bishop.h"

namespace chess {

Bishop::Bishop(Colour colour) : Piece{colour == Colour::White ? "♗" : "♝", colour} {
}

}
