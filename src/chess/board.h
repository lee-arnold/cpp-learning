#pragma once

#include <array>
#include <memory>
#include <vector>

#include "chess/colour.h"
#include "chess/pieces/piece.h"
#include "chess/position.h"

namespace chess {

class Board {
  public:
    Board();

    constexpr int dimension() const {
        return static_cast<int>(board_.size());
    }

    static constexpr bool is_inside(Position position) {
        return !(
            position.file() < 0 || position.file() > 7 || position.rank() < 0 || position.rank() > 7
        );
    }

    bool is_empty(Position position) const;

    // both a const and non const version, one for setting one for reading
    // the compiler chooses which based on whether the board itself is const
    std::unique_ptr<Piece> &operator[](Position position);
    const Piece *operator[](Position position) const;
    bool is_in_check(Colour player) const;
    Board copy() const;

  private:
    struct Empty {};

    explicit Board(Empty);
    void initialise();
    // prefer this over board_[8][8]
    std::array<std::array<std::unique_ptr<Piece>, 8>, 8> board_;
    std::vector<Position> piece_positions() const;
    std::vector<Position> piece_positions_for(Colour player) const;
};

}
