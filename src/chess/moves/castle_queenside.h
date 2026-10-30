#pragma once

#include "chess/moves/move.h"

namespace chess {

class Position;
class Board;

class CastleQueenSide : public Move {
  public:
    explicit CastleQueenSide(Position from);
    void execute(Board &board) const override;
};

}
