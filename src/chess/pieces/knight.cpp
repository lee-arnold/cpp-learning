#include "chess/pieces/knight.h"
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

constexpr auto rank_directions = std::array<chess::Direction, 2>{
    chess::Direction::north(),
    chess::Direction::south(),
};
constexpr auto file_directions = std::array<chess::Direction, 2>{
    chess::Direction::east(),
    chess::Direction::west(),
};

}

namespace chess {

Knight::Knight(Colour colour)
    : Piece{colour, PieceType::Knight} {
}

std::vector<std::unique_ptr<Move>> Knight::get_moves(Position from, const Board &board) const {
    std::vector<std::unique_ptr<Move>> moves{};

    for (auto rank : rank_directions) {
        for (auto file : file_directions) {
            auto to_1 = Position{from + rank * 2 + file};
            auto to_2 = Position{from + file * 2 + rank};

            if (Board::is_inside(to_1) &&
                (board.is_empty(to_1) || board[to_1]->colour() != colour())) {
                moves.push_back(std::make_unique<NormalMove>(from, to_1));
            }

            if (Board::is_inside(to_2) &&
                (board.is_empty(to_2) || board[to_2]->colour() != colour())) {
                moves.push_back(std::make_unique<NormalMove>(from, to_2));
            }
        }
    }

    return moves;
}

std::unique_ptr<Piece> Knight::copy() const {
    return std::make_unique<Knight>(*this);
}

}
