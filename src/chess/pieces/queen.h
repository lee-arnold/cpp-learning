#pragma once

#include "chess/colour.h"
#include "chess/pieces/piece.h"

namespace chess {

class Queen : public Piece {
  public:
    Queen(Colour colour);
};

}
