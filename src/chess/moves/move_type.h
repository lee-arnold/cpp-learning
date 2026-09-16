#pragma once

namespace chess {

enum class MoveType {
    Normal,
    CastleKingSide,
    CastleQueenSide,
    DoublePawnAdvance,
    EnPassant,
    PawnPromotion
};

}
