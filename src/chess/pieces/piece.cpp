#include "chess/pieces/piece.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/direction.h"
#include "chess/moves/move.h"
#include "chess/moves/normal.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include <memory>
#include <ranges>
#include <span>
#include <vector>

namespace chess {

Piece::Piece(Colour colour, PieceType type)
    : colour_{colour},
      type_{type} {
}

Colour Piece::colour() const {
    return colour_;
}

PieceType Piece::type() const {
    return type_;
}

bool Piece::has_moved() const {
    return has_moved_;
}

void Piece::set_has_moved() {
    has_moved_ = true;
}

std::vector<std::unique_ptr<Move>> Piece::get_moves_in_direction(
    Position from, const Board &board, Direction direction
) const {
    auto moves = std::vector<std::unique_ptr<Move>>{};

    for (auto position = from + direction; Board::is_inside(position); position += direction) {
        if (board.is_empty(position)) {
            moves.push_back(std::make_unique<NormalMove>(from, position));
            continue;
        }

        const auto *piece = board[position];

        if (piece->colour() != colour()) {
            moves.push_back(std::make_unique<NormalMove>(from, position));
        }

        break;
    }

    return moves;
}

std::vector<std::unique_ptr<Move>> Piece::get_moves_in_directions(
    Position from, const Board &board, std::span<const Direction> directions
) const {
    auto moves = std::vector<std::unique_ptr<Move>>{};

    for (auto direction : directions) {
        moves.append_range(get_moves_in_direction(from, board, direction) | std::views::as_rvalue);
    }

    return moves;
}

}
