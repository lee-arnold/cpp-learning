#include "piece.h"
#include "colour.h"

#include <string_view>

namespace chess {

Piece::Piece(std::string_view icon, Colour colour) : icon_{icon}, colour_{colour} {
}

std::string_view Piece::icon() const {
    return icon_;
}

Colour Piece::colour() const {
    return colour_;
}

}
