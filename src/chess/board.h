#pragma once

#include <array>
#include <memory>

#include "chess/pieces/piece.h"

namespace chess {

class Position;

class Board {
  public:
    Board();

    constexpr int dimension() const {
        return static_cast<int>(board_.size());
    }

    // both a const and non const version, one for setting one for reading
    // the compiler chooses which based on whether the board itself is const
    std::array<std::unique_ptr<Piece>, 8> &operator[](int rank);
    const std::array<std::unique_ptr<Piece>, 8> &operator[](int rank) const;
    std::unique_ptr<Piece> &operator[](Position position);
    const std::unique_ptr<Piece> &operator[](Position position) const;

  private:
    void initialise();
    // prefer this over board_[8][8]
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board_;
};

}
