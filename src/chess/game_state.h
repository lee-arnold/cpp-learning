#pragma once

#include "chess/board.h"
#include "chess/colour.h"
#include "chess/moves/move.h"
#include "chess/position.h"
#include <memory>
#include <vector>

namespace chess {

class GameState {
  public:
    GameState(Colour player, Board &board);
    std::vector<std::unique_ptr<Move>> available_moves_for_piece(const Position position) const;
    Colour current_player() const;
    void execute_move(const Move &move);

  private:
    Board &board_;
    Colour current_player_;
};

}
