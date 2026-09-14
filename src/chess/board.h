#pragma once

#include <array>
#include <memory>

#include "chess/position.h"
#include "piece.h"

namespace chess {

class Board {
  public:
    Board();
    // const so that we know print isn't modifying anything on the object it was called on
    void print() const;

    // both a const and non const version, one for setting one for reading
    // the compiler chooses which based on whether the board itself is const
    std::unique_ptr<Piece> &operator[](Position position);
    const std::unique_ptr<Piece> &operator[](Position position) const;
    std::unique_ptr<Piece> &operator[](int rank, int file);
    const std::unique_ptr<Piece> &operator[](int rank, int file) const;

  private:
    void initialise();
    // prefer this over board_[8][8]
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board_;
};

}
