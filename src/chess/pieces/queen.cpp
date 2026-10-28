#include "chess/pieces/queen.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/direction.h"
#include "chess/moves/move.h"
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

Queen::Queen(Colour colour)
    : Piece{colour, PieceType::Queen} {
}

std::vector<std::unique_ptr<Move>> Queen::get_moves(Position from, const Board &board) const {
    return get_moves_in_directions(from, board, directions);
}

}
