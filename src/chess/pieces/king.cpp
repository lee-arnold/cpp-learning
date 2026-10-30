#include "chess/pieces/king.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/direction.h"
#include "chess/moves/castle_kingside.h"
#include "chess/moves/castle_queenside.h"
#include "chess/moves/move.h"
#include "chess/moves/normal.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"
#include "chess/pieces/rook.h"
#include "chess/position.h"

#include <array>
#include <memory>
#include <ranges>
#include <vector>

namespace {

constexpr auto directions = std::array<chess::Direction, 8>{
    chess::Direction::north(),
    chess::Direction::east(),
    chess::Direction::south(),
    chess::Direction::west(),
    chess::Direction::northwest(),
    chess::Direction::northeast(),
    chess::Direction::southwest(),
    chess::Direction::southeast(),
};

}

namespace chess {

King::King(Colour colour)
    : Piece{colour, PieceType::King} {
}

std::vector<std::unique_ptr<Move>> King::get_moves(Position from, const Board &board) const {
    std::vector<std::unique_ptr<Move>> moves{};

    moves.append_range(get_normal_moves(from, board) | std::views::as_rvalue);
    moves.append_range(get_castling_moves(from, board) | std::views::as_rvalue);

    return moves;
}

std::vector<std::unique_ptr<Move>> King::get_normal_moves(Position from, const Board &board) const {
    std::vector<std::unique_ptr<Move>> moves{};

    for (auto direction : directions) {
        auto to = from + direction;

        if (!Board::is_inside(to)) continue;

        if (board.is_empty(to) || board[to]->colour() != colour()) {
            moves.push_back(std::make_unique<NormalMove>(from, to));
        }
    }

    return moves;
}

std::vector<std::unique_ptr<Move>> King::get_castling_moves(
    Position from, const Board &board
) const {
    std::vector<std::unique_ptr<Move>> moves{};

    if (can_castle(board, from, Direction::east())) {
        moves.push_back(std::make_unique<CastleKingSide>(from));
    }

    if (can_castle(board, from, Direction::west())) {
        moves.push_back(std::make_unique<CastleQueenSide>(from));
    }

    return moves;
}

bool King::can_castle(const Board &board, Position from, Direction direction) const {
    if (has_moved() || board.is_in_check(colour())) return false;

    auto piece = direction == Direction::east() ? board[Position{from.rank(), 7}]
                                                : board[Position{from.rank(), 0}];
    auto *rook = dynamic_cast<const Rook *>(piece);

    if (!rook) return false;
    if (rook->colour() != colour()) return false;
    if (rook->has_moved()) return false;

    const bool kingside = direction == Direction::east();
    const int first_file = kingside ? 5 : 1;
    const int last_file = kingside ? 6 : 3;

    for (int file = first_file; file <= last_file; ++file) {
        if (!board.is_empty(Position{from.rank(), file})) return false;
    }

    const int first_king_file = kingside ? 5 : 2;
    for (int file = first_king_file; file <= last_file; ++file) {
        auto copy = board.copy();
        auto move = NormalMove{from, Position{from.rank(), file}};
        move.execute(copy);
        if (copy.is_in_check(colour())) return false;
    }

    return true;
}

std::unique_ptr<Piece> King::copy() const {
    return std::make_unique<King>(*this);
}

bool King::can_capture_opponent_king(Position from, const Board &board) const {
    auto moves = get_normal_moves(from, board);

    for (auto &move : moves) {
        auto piece = board[move->to()];

        if (piece && piece->type() == PieceType::King) return true;
    }

    return false;
}

}
