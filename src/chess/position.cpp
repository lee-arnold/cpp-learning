#include "chess/position.h"
#include "chess/colour.h"
#include "chess/utils.h"

namespace chess {

constexpr Colour Position::squareColour() const {
    return is_even(rank_ + file_) ? Colour::Black : Colour::White;
}

}
