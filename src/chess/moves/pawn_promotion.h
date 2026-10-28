#pragma once

#include "chess/colour.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"
#include <memory>

namespace chess {

class Position;
class Board;

class PawnPromotionMove : public Move {
  public:
    PawnPromotionMove(Position from, Position to, PieceType piece_type);
    void execute(Board &board) const override;
    PieceType piece_type() const;

  private:
    PieceType piece_type_;
    std::unique_ptr<Piece> create_promotion_piece(Colour colour) const;
};

}
