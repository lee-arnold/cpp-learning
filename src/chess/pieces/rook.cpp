#include "rook.h"
#include "chess/colour.h"
#include "chess/piece.h"

namespace chess {

Rook::Rook(Colour colour) : Piece{colour == Colour::White ? "♖" : "♜", colour} {
}

}
