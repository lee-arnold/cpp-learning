#pragma once

#include "chess/colour.h"
#include "chess/piece.h"

namespace chess {

class Pawn : public Piece {
  public:
    Pawn(Colour colour);
};

}
