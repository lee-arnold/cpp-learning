#include "rook.h"
#include "chess/colour.h"
#include "chess/piece.h"
#include "chess/piece_type.h"

namespace chess {

Rook::Rook(Colour colour) : Piece{colour == Colour::White ? "♖" : "♜", colour, PieceType::Rook} {
}

}
