#pragma once

#include "chess/colour.h"
#include "chess/pieces/piece_type.h"
#include <string_view>

namespace chess {

class Piece {
  public:
    std::string_view icon() const;
    Colour colour() const;
    PieceType type() const;
    virtual ~Piece() = default;

  protected:
    // protected prevents creation of random pieces outside of classes that inherit
    Piece(std::string_view icon, Colour colour, PieceType type);

  private:
    // private prevents us from writing to these variables
    std::string_view icon_;
    Colour colour_;
    PieceType type_;
};

}
