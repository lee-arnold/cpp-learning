#pragma once

#include "chess/position.h"

namespace terminal {

struct RequestedMove {
    chess::Position from;
    chess::Position to;
};

RequestedMove get_move_from_user();

}
