#pragma once

#include "chess/board.h"
#include "chess/moves/move.h"
#include "chess/position.h"

namespace chess {

class NormalMove : public Move {
  public:
    NormalMove(Position from, Position to);
    void execute(Board &board) const override;
};

}
