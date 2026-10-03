#pragma once

#include "chess/colour.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include <memory>
#include <vector>

namespace chess {

class Piece {
  public:
    Colour colour() const;
    PieceType type() const;
    bool has_moved() const;
    void set_has_moved();
    virtual std::vector<std::unique_ptr<Move>> get_moves(
        Position position, const Board &board
    ) const = 0;
    virtual ~Piece() = default;

  protected:
    // protected prevents creation of random pieces outside of classes that inherit
    Piece(Colour colour, PieceType type);

  private:
    // private prevents us from writing to these variables
    Colour colour_;
    PieceType type_;
    bool has_moved_{false};
};

}
