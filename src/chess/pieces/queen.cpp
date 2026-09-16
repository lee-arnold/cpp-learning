#include "chess/pieces/queen.h"
#include "chess/colour.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"

namespace chess {

Queen::Queen(Colour colour) : Piece{colour == Colour::White ? "♕" : "♛", colour, PieceType::Queen} {
}

}
