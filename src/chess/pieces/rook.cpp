#include "chess/pieces/rook.h"
#include "chess/colour.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"

namespace chess {

Rook::Rook(Colour colour) : Piece{colour == Colour::White ? "♖" : "♜", colour, PieceType::Rook} {
}

}
