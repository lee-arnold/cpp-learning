#include "chess/pieces/king.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/direction.h"
#include "chess/moves/move.h"
#include "chess/moves/normal.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include <array>
#include <memory>
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
    return get_normal_moves(from, board);
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

}
