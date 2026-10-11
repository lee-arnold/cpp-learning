#include "chess/pieces/queen.h"
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

Queen::Queen(Colour colour)
    : Piece{colour, PieceType::Queen},
      directions_{std::vector<Direction>{
          Direction::North(),
          Direction::East(),
          Direction::South(),
          Direction::West(),
          Direction::NorthWest(),
          Direction::NorthEast(),
          Direction::SouthWest(),
          Direction::SouthEast(),
      }} {
}

std::vector<std::unique_ptr<Move>> Queen::get_moves(Position position, const Board &board) const {
    return get_moves_in_directions(position, board, directions_);
}

}
