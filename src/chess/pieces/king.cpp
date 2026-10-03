#include "chess/pieces/king.h"
#include "chess/colour.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"

namespace chess {

King::King(Colour colour) : Piece{colour, PieceType::King} {
}

}
