#include "chess/pieces/piece.h"
#include "chess/colour.h"
#include "chess/direction.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include <memory>
#include <vector>

namespace chess {

Piece::Piece(Colour colour, PieceType type) : colour_{colour}, type_{type} {
}

Colour Piece::colour() const {
    return colour_;
}

PieceType Piece::type() const {
    return type_;
}

bool Piece::has_moved() const {
    return has_moved_;
}

void Piece::set_has_moved() {
    has_moved_ = true;
}

std::vector<std::unique_ptr<Move>> Piece::get_moves_in_direction(
    const Position position, const Board &board, const Direction direction
) {
    auto moves = std::vector<std::unique_ptr<Move>>{};

    return moves;
}

std::vector<std::unique_ptr<Move>> Piece::get_moves_in_directions(
    const Position position, const Board &board, const std::vector<Direction> direction
) {
    auto moves = std::vector<std::unique_ptr<Move>>{};

    return moves;
}

}
