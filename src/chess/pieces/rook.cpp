#include "rook.h"

namespace chess {

Rook::Rook(Colour colour) : Piece{colour == Colour::White ? "♖" : "♜", colour} {
}

}
