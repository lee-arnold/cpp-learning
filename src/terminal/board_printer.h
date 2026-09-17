#pragma once

#include "chess/board.h"

namespace terminal {

class BoardPrinter {
  public:
    constexpr BoardPrinter(const chess::Board &board) : board_{board} {
    }

    void print() const;

  private:
    const chess::Board &board_;
};

}
