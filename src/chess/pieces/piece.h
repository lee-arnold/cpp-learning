#pragma once

#include "chess/colour.h"
#include "chess/direction.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include <memory>
#include <span>
#include <vector>

namespace chess {

class Piece {
  public:
    Colour colour() const;
    PieceType type() const;
    bool has_moved() const;
    void set_has_moved();
    virtual std::vector<std::unique_ptr<Move>> get_moves(
        Position from, const Board &board
    ) const = 0;
    virtual std::unique_ptr<Piece> copy() const = 0;
    virtual ~Piece() = default;
    virtual bool can_capture_opponent_king(Position from, const Board &board) const;

  protected:
    // protected prevents creation of random pieces outside of classes that inherit
    Piece(Colour colour, PieceType type);
    std::vector<std::unique_ptr<Move>> get_moves_in_direction(
        Position from, const Board &board, Direction direction
    ) const;
    std::vector<std::unique_ptr<Move>> get_moves_in_directions(
        Position from, const Board &board, std::span<const Direction> direction
    ) const;

  private:
    // private prevents us from writing to these variables from outside of this class
    Colour colour_;
    PieceType type_;
    bool has_moved_{false};
};

}
