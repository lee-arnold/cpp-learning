#include "king.h"
#include "chess/colour.h"
#include "chess/piece.h"
#include "chess/piece_type.h"

namespace chess {

King::King(Colour colour) : Piece{colour == Colour::White ? "♔" : "♚", colour, PieceType::King} {
}

}
