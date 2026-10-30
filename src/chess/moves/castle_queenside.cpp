#include "chess/moves/castle_queenside.h"
#include "chess/board.h"
#include "chess/moves/move.h"
#include "chess/moves/move_type.h"
#include <utility>

namespace chess {

CastleQueenSide::CastleQueenSide(Position from)
    : Move{MoveType::CastleQueenSide, from, Position{from.rank(), 2}} {
}

void CastleQueenSide::execute(Board &board) const {
    auto &piece = board[from()];

    piece->set_has_moved();
    board[to()] = std::move(board[from()]);

    auto rook_from = Position{from().rank(), 0};
    auto rook_to = Position{from().rank(), 3};
    auto &rook = board[rook_from];

    rook->set_has_moved();
    board[rook_to] = std::move(board[rook_from]);
}

}
