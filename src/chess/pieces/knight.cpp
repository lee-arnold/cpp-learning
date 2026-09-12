#include "knight.h"
#include "chess/colour.h"
#include "chess/piece.h"

namespace chess {

Knight::Knight(Colour colour) : Piece{colour == Colour::White ? "♘" : "♞", colour} {
}

}
