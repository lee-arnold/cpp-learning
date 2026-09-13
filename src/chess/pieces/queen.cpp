#include "queen.h"
#include "chess/colour.h"
#include "chess/piece.h"
#include "chess/piece_type.h"

namespace chess {

Queen::Queen(Colour colour) : Piece{colour == Colour::White ? "♕" : "♛", colour, PieceType::Queen} {
}

}
