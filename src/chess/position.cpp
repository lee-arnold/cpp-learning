#include "position.h"
#include "colour.h"
#include "utils.h"

namespace chess {

constexpr Colour Position::squareColour() const {
    return is_even(rank_ + file_) ? Colour::Black : Colour::White;
}

}
