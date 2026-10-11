#include "chess/pieces/rook.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/direction.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include <memory>
#include <vector>

namespace chess {

Rook::Rook(Colour colour)
    : Piece{colour, PieceType::Rook},
      directions_{std::vector<Direction>{
          Direction::North(),
          Direction::East(),
          Direction::South(),
          Direction::West(),
      }} {
}

std::vector<std::unique_ptr<Move>> Rook::get_moves(Position from, const Board &board) const {
    return get_moves_in_directions(from, board, directions_);
}

}
