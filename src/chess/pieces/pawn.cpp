#include "chess/pieces/pawn.h"
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

Pawn::Pawn(Colour colour)
    : Piece{colour, PieceType::Pawn},
      forward_{colour == Colour::White ? Direction::North() : Direction::South()} {
}

std::vector<std::unique_ptr<Move>> Pawn::get_moves(Position from, const Board &board) const {
    std::vector<std::unique_ptr<Move>> moves;

    moves.append_range(get_forward_moves(from, board) | std::views::as_rvalue);
    moves.append_range(get_diagonal_moves(from, board) | std::views::as_rvalue);

    return moves;
}

std::vector<std::unique_ptr<Move>> Pawn::get_forward_moves(
    Position from, const Board &board
) const {
    std::vector<std::unique_ptr<Move>> moves;

    auto one_forward = from + forward_;

    if (board.is_inside(one_forward) && board.is_empty(one_forward)) {
        moves.push_back(std::make_unique<NormalMove>(from, one_forward));
    } else {
        return moves;
    }

    auto two_forward = one_forward + forward_;

    if (!this->has_moved() && board.is_inside(two_forward) && board.is_empty(two_forward)) {
        moves.push_back(std::make_unique<NormalMove>(from, two_forward));
    }

    return moves;
}

std::vector<std::unique_ptr<Move>> Pawn::get_diagonal_moves(
    Position from [[maybe_unused]], const Board &board [[maybe_unused]]
) const {
    return std::vector<std::unique_ptr<Move>>{};
}

}
