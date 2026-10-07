#pragma once

#include "chess/board.h"
#include "chess/game_state.h"
#include "chess/position.h"
#include <vector>

void relocate_piece(
    chess::Board &board, chess::Position from, chess::Position to, bool set_has_moved = false
);

std::vector<chess::Position> get_destinations_for_piece(
    const chess::GameState &game, const chess::Position from
);
