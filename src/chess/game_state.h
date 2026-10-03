#pragma once

#include "chess/board.h"
#include "chess/moves/move.h"
#include "chess/position.h"
#include <memory>
#include <vector>

namespace chess {

class GameState {
  public:
    GameState(const Board &board);
    std::vector<std::unique_ptr<Move>> legal_moves_for_piece(const Position position);

  private:
    const Board &board_;
};

}
