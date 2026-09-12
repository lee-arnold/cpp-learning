#pragma once

#include "chess/colour.h"
#include "chess/piece.h"

namespace chess {

class Queen : public Piece {
  public:
    Queen(Colour colour);
};

}
