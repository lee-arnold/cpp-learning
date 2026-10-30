#include "chess/pieces/rook.h"
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

constexpr auto directions = std::array<chess::Direction, 4>{
    chess::Direction::north(),
    chess::Direction::east(),
    chess::Direction::south(),
    chess::Direction::west(),
};

}

namespace chess {

Rook::Rook(Colour colour)
    : Piece{colour, PieceType::Rook} {
}

std::vector<std::unique_ptr<Move>> Rook::get_moves(Position from, const Board &board) const {
    return get_moves_in_directions(from, board, directions);
}

std::unique_ptr<Piece> Rook::copy() const {
    return std::make_unique<Rook>(*this);
}

}
