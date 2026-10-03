#pragma once

#include "chess/board.h"
#include "chess/colour.h"
#include "chess/direction.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece.h"
#include "chess/position.h"
#include <memory>
#include <vector>

namespace chess {

class Pawn : public Piece {
  public:
    Pawn(Colour colour);
    std::vector<std::unique_ptr<Move>> get_moves(
        Position position, const Board &board
    ) const override;

  private:
    Direction forward_;
    std::vector<std::unique_ptr<Move>> get_forward_moves(
        Position position, const Board &board
    ) const;
    std::vector<std::unique_ptr<Move>> get_diagonal_moves(
        Position position, const Board &board
    ) const;

    constexpr static bool can_move_to(Position position, const Board &board) {
        return board.is_empty(position) && board.is_inside(position);
    }
};

}
