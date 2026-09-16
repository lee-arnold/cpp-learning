#pragma once

#include "chess/colour.h"
#include "chess/pieces/piece.h"

namespace chess {

class Pawn : public Piece {
  public:
    Pawn(Colour colour);
};

}
