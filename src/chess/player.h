#pragma once

#include "chess/colour.h"

#include <stdexcept>

namespace chess {

constexpr Colour opponent(Colour colour) {
    switch (colour) {
        case Colour::White:
            return Colour::Black;
        case Colour::Black:
            return Colour::White;
        default:
            throw std::runtime_error("Unrecognised player colour");
    }
}

}
