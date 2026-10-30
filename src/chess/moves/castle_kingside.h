#pragma once

#include "chess/moves/move.h"

namespace chess {

class Position;
class Board;

class CastleKingSide : public Move {
  public:
    explicit CastleKingSide(Position from);
    void execute(Board &board) const override;
};

}
