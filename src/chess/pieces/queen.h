#pragma once

#include "chess/colour.h"
#include "chess/direction.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece.h"
#include "chess/position.h"
#include <memory>
#include <vector>

namespace chess {

class Queen : public Piece {
  public:
    explicit Queen(Colour colour);
    std::vector<std::unique_ptr<Move>> get_moves(Position from, const Board &board) const override;

  private:
    std::vector<Direction> directions_;
};

}
