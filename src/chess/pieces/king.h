#pragma once

#include "chess/colour.h"
#include "chess/pieces/piece.h"

namespace chess {

class King : public Piece {
  public:
    King(Colour colour);
};

}
