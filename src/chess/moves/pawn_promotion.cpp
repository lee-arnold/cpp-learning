#include "chess/moves/pawn_promotion.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/moves/move.h"
#include "chess/moves/move_type.h"
#include "chess/pieces/bishop.h"
#include "chess/pieces/knight.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/piece_type.h"
#include "chess/pieces/queen.h"
#include "chess/pieces/rook.h"
#include "chess/position.h"
#include <memory>
#include <stdexcept>
#include <utility>

namespace chess {

PawnPromotionMove::PawnPromotionMove(Position from, Position to, PieceType piece_type)
    : Move{MoveType::PawnPromotion, from, to},
      piece_type_{piece_type} {
}

std::unique_ptr<Piece> PawnPromotionMove::create_promotion_piece(Colour colour) const {
    switch (piece_type_) {
        case PieceType::Queen:
            return std::make_unique<Queen>(colour);
        case PieceType::Rook:
            return std::make_unique<Rook>(colour);
        case PieceType::Bishop:
            return std::make_unique<Bishop>(colour);
        case PieceType::Knight:
            return std::make_unique<Knight>(colour);
        default:
            throw std::invalid_argument("Invalid pawn promotion");
    }
}

PieceType PawnPromotionMove::piece_type() const {
    return piece_type_;
}

void PawnPromotionMove::execute(Board &board) const {
    auto &piece = board[from()];
    auto promoted_piece = create_promotion_piece(piece->colour());

    promoted_piece->set_has_moved();

    board[from()] = nullptr;
    board[to()] = std::move(promoted_piece);
}

}
