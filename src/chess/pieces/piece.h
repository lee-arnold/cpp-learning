#pragma once

#include "chess/colour.h"
#include "chess/pieces/piece_type.h"

namespace chess {

class Piece {
  public:
    Colour colour() const;
    PieceType type() const;
    virtual ~Piece() = default;

  protected:
    // protected prevents creation of random pieces outside of classes that inherit
    Piece(Colour colour, PieceType type);

  private:
    // private prevents us from writing to these variables
    Colour colour_;
    PieceType type_;
};

}
