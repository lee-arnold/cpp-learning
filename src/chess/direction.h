#pragma once

namespace chess {

class Direction {
  public:
    constexpr Direction(int rank_delta, int file_delta)
        : rank_delta_{rank_delta}, file_delta_{file_delta} {
    }

    constexpr static Direction North() {
        return Direction{-1, 0};
    }

    constexpr static Direction South() {
        return Direction{1, 0};
    }

    constexpr static Direction East() {
        return Direction{0, 1};
    }

    constexpr static Direction West() {
        return Direction{0, -1};
    }

    constexpr static Direction NorthWest() {
        return Direction::North() + Direction::West();
    }

    constexpr static Direction NorthEast() {
        return Direction::North() + Direction::East();
    }

    constexpr static Direction SouthWest() {
        return Direction::South() + Direction::West();
    }

    constexpr static Direction SouthEast() {
        return Direction::South() + Direction::East();
    }

    constexpr Direction operator+(Direction direction) const {
        return Direction{rank_delta_ + direction.rank_delta_, file_delta_ + direction.file_delta_};
    }

  private:
    int rank_delta_;
    int file_delta_;
};

}
