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
    King(Colour colour);
    std::vector<std::unique_ptr<Move>> get_moves(
        Position position, const Board &board
    ) const override;
};

}
