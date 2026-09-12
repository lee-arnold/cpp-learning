#pragma once

#include <memory>

#include "piece.h"

namespace chess {

class Board {
  public:
    Board();
    // const so that we know print isn't modifying anything on the object it was called on
    void print() const;

  private:
    void initialise();
    // prefer this over board_[8][8]
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board_;
};

}
