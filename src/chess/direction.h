#pragma once

namespace chess {

class Direction {
  public:
    constexpr Direction(int rank_delta, int file_delta)
        : rank_delta_{rank_delta},
          file_delta_{file_delta} {
    }

    constexpr int rank_delta() const {
        return rank_delta_;
    }

    constexpr int file_delta() const {
        return file_delta_;
    }

    static constexpr Direction north() {
        return Direction{1, 0};
    }

    static constexpr Direction south() {
        return Direction{-1, 0};
    }

    static constexpr Direction east() {
        return Direction{0, 1};
    }

    static constexpr Direction west() {
        return Direction{0, -1};
    }

    static constexpr Direction northwest() {
        return Direction::north() + Direction::west();
    }

    static constexpr Direction northeast() {
        return Direction::north() + Direction::east();
    }

    static constexpr Direction southwest() {
        return Direction::south() + Direction::west();
    }

    static constexpr Direction southeast() {
        return Direction::south() + Direction::east();
    }

    constexpr Direction operator+(Direction direction) const {
        return Direction{rank_delta_ + direction.rank_delta_, file_delta_ + direction.file_delta_};
    }

    constexpr Direction operator*(int scalar) const {
        return Direction{rank_delta_ * scalar, file_delta_ * scalar};
    }

  private:
    int rank_delta_;
    int file_delta_;
};

}
