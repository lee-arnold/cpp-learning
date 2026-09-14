#pragma once

#include "chess/board.h"
#include "chess/move.h"
#include "chess/position.h"

namespace chess {

class Normal : public Move {
  public:
    Normal(Position from, Position to);
    void execute(Board &board) const override;
};

}
