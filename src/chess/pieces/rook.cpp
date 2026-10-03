#include "chess/pieces/rook.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include <memory>
#include <vector>

namespace chess {

Rook::Rook(Colour colour) : Piece{colour, PieceType::Rook} {
}

std::vector<std::unique_ptr<Move>> Rook::get_moves(
    Position position [[maybe_unused]], const Board &board [[maybe_unused]]
) const {
    return std::vector<std::unique_ptr<Move>>{};
}

}
