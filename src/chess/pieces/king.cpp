#include "chess/pieces/king.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/direction.h"
#include "chess/moves/move.h"
#include "chess/moves/normal.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include <memory>
#include <ranges>
#include <vector>

namespace chess {

King::King(Colour colour)
    : Piece{colour, PieceType::King},
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

std::vector<std::unique_ptr<Move>> King::get_moves(Position from, const Board &board) const {
    std::vector<std::unique_ptr<Move>> moves;

    moves.append_range(get_normal_moves(from, board) | std::views::as_rvalue);

    return moves;
}

std::vector<std::unique_ptr<Move>> King::get_normal_moves(Position from, const Board &board) const {
    std::vector<std::unique_ptr<Move>> moves{};

    for (auto direction : directions_) {
        auto to = from + direction;

        if (!Board::is_inside(to)) continue;

        if (board.is_empty(to) || board[to]->colour() != colour()) {
            moves.push_back(std::make_unique<NormalMove>(from, to));
        }
    }

    return moves;
}

}
