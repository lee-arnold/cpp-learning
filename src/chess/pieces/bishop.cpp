#include "chess/pieces/bishop.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include <memory>
#include <vector>

namespace chess {

Bishop::Bishop(Colour colour) : Piece{colour, PieceType::Bishop} {
}

std::vector<std::unique_ptr<Move>> Bishop::get_moves(
    Position position [[maybe_unused]], const Board &board [[maybe_unused]]
) const {
    return std::vector<std::unique_ptr<Move>>{};
}

}
