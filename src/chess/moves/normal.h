#pragma once

#include "chess/moves/move.h"

namespace chess {

class Position;
class Board;

class NormalMove : public Move {
  public:
    NormalMove(Position from, Position to);
    void execute(Board &board) const override;
};

}
