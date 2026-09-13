#include "position.h"
#include "colour.h"
#include "utils.h"

namespace chess {

constexpr Position::Position(int rank, int file) : rank_{rank}, file_{file} {
}

constexpr int Position::rank() const {
    return rank_;
}

constexpr int Position::file() const {
    return file_;
}

constexpr Colour Position::squareColour() const {
    return is_even(rank_ + file_) ? Colour::Black : Colour::White;
}

}
