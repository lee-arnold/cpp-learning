#pragma once

#include "chess/colour.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece.h"
#include "chess/position.h"
#include <memory>
#include <vector>

namespace chess {

class King : public Piece {
  public:
    explicit King(Colour colour);
    std::vector<std::unique_ptr<Move>> get_moves(Position from, const Board &board) const override;

  private:
    std::vector<std::unique_ptr<Move>> get_normal_moves(Position from, const Board &board) const;
};

}
