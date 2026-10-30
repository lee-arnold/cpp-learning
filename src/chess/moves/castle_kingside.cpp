#include "chess/moves/castle_kingside.h"
#include "chess/board.h"
#include "chess/moves/move.h"
#include "chess/moves/move_type.h"
#include <utility>

namespace chess {

CastleKingSide::CastleKingSide(Position from)
    : Move{MoveType::CastleKingSide, from, Position{from.rank(), 6}} {
}

void CastleKingSide::execute(Board &board) const {
    auto &piece = board[from()];

    piece->set_has_moved();
    board[to()] = std::move(board[from()]);

    auto rook_from = Position{from().rank(), 7};
    auto rook_to = Position{from().rank(), 5};
    auto &rook = board[rook_from];

    rook->set_has_moved();
    board[rook_to] = std::move(board[rook_from]);
}

}
