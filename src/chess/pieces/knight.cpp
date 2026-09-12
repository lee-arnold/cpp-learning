#include "knight.h"

namespace chess {

Knight::Knight(Colour colour) : Piece{colour == Colour::White ? "♘" : "♞", colour} {
}

}
