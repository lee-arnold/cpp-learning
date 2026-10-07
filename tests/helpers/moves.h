#include "chess/board.h"
#include "chess/position.h"

void relocate_piece(
    chess::Board &board, chess::Position from, chess::Position to, bool set_has_moved = false
);
