#pragma once

#include "chess/position.h"
#include <string_view>

namespace chess {

bool constexpr is_valid_move_format(std::string_view chess_notation) {
    return !(chess_notation.length() != 2 || chess_notation[0] < 'a' || chess_notation[0] > 'h' ||
             chess_notation[1] < '1' || chess_notation[1] > '8');
}

constexpr Position parse_position(std::string_view chess_notation) {
    int file = chess_notation[0] - 'a';
    int rank = chess_notation[1] - '1';

    return Position{rank, file};
}

}
