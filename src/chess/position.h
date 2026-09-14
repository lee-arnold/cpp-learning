#pragma once

#include "colour.h"

namespace chess {

class Position {
  public:
    constexpr Position(int rank, int file) : rank_{rank}, file_{file} {
    }

    constexpr int rank() const {
        return rank_;
    }

    constexpr int file() const {
        return file_;
    }

    constexpr Colour squareColour() const;

    // this tells c++ to check the object members are the same and does the default equality
    // compare this position against another existing position without copying or modifying either
    constexpr bool operator==(const Position &) const = default;

  private:
    int rank_;
    int file_;
};

}
