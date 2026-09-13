#pragma once

#include "chess/utils.h"
#include "colour.h"

namespace chess {

class Position {
  public:
    constexpr Position(int rank, int file);

    constexpr int rank() const;
    constexpr int file() const;

    constexpr Colour squareColour() const;

    // this tells c++ to check the object members are the same and does the default equality
    // compare this position against another existing position without copying or modifying either
    constexpr bool operator==(const Position &) const = default;

  private:
    int rank_;
    int file_;
};

}
