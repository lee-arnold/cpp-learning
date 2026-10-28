#include "chess/pieces/bishop.h"
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
    chess::Direction::northwest(),
    chess::Direction::northeast(),
    chess::Direction::southwest(),
    chess::Direction::southeast(),
};

}

namespace chess {

Bishop::Bishop(Colour colour)
    : Piece{colour, PieceType::Bishop} {
}

std::vector<std::unique_ptr<Move>> Bishop::get_moves(Position position, const Board &board) const {
    return get_moves_in_directions(position, board, directions);
}

}
