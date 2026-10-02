#pragma once

#include <array>
#include <memory>

#include "chess/pieces/piece.h"
#include "chess/position.h"

namespace chess {

class Board {
  public:
    Board();

    constexpr int dimension() const {
        return static_cast<int>(board_.size());
    }

    constexpr static bool is_inside(Position position) {
        return !(
            position.file() < 0 || position.file() > 7 || position.rank() < 0 || position.rank() > 7
        );
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
