#include "chess/pieces/pawn.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/direction.h"
#include "chess/moves/move.h"
#include "chess/moves/normal.h"
#include "chess/moves/pawn_promotion.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"

#include <array>
#include <memory>
#include <ranges>
#include <vector>

namespace {

constexpr auto file_directions = std::array<chess::Direction, 2>{
    chess::Direction::east(),
    chess::Direction::west(),
};

}

namespace chess {

Pawn::Pawn(Colour colour)
    : Piece{colour, PieceType::Pawn},
      forward_{colour == Colour::White ? Direction::north() : Direction::south()} {
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

    if (!board.is_inside(one_forward) || !board.is_empty(one_forward)) return moves;

    if (one_forward.rank() == 0 || one_forward.rank() == 7) {
        return get_promotion_moves(from, one_forward);
    }

    moves.push_back(std::make_unique<NormalMove>(from, one_forward));

    auto two_forward = one_forward + forward_;

    if (!this->has_moved() && board.is_inside(two_forward) && board.is_empty(two_forward)) {
        moves.push_back(std::make_unique<NormalMove>(from, two_forward));
    }

    return moves;
}

bool Pawn::can_capture_at(Position position, const Board &board) const {
    if (!Board::is_inside(position) || board.is_empty(position)) {
        return false;
    }

    return board[position]->colour() != colour();
}

std::vector<std::unique_ptr<Move>> Pawn::get_diagonal_moves(
    Position from, const Board &board
) const {
    std::vector<std::unique_ptr<Move>> moves;

    for (auto file : file_directions) {
        Position to = from + forward_ + file;
        if (can_capture_at(to, board)) {
            if (to.rank() == 0 || to.rank() == 7) {
                moves.append_range(get_promotion_moves(from, to) | std::views::as_rvalue);
            } else {
                moves.push_back(std::make_unique<NormalMove>(from, to));
            }
        }

        // @TODO implement en passant
    }

    return moves;
}

std::vector<std::unique_ptr<Move>> Pawn::get_promotion_moves(Position from, Position to) const {
    std::vector<std::unique_ptr<Move>> moves;

    moves.push_back(std::make_unique<PawnPromotionMove>(from, to, PieceType::Queen));
    moves.push_back(std::make_unique<PawnPromotionMove>(from, to, PieceType::Rook));
    moves.push_back(std::make_unique<PawnPromotionMove>(from, to, PieceType::Bishop));
    moves.push_back(std::make_unique<PawnPromotionMove>(from, to, PieceType::Knight));

    return moves;
}

}
