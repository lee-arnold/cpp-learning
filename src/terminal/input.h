#pragma once

#include "chess/position.h"
#include <optional>

namespace terminal {

struct RequestedMove {
    chess::Position from;
    chess::Position to;
};

std::optional<RequestedMove> get_move_from_user();

}
