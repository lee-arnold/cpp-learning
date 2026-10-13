#pragma once

#include "chess/board.h"
#include "chess/colour.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <string_view>

namespace gui {

struct TextureAsset {
    chess::PieceType type;
    chess::Colour colour;
    std::string_view filename;
};

constexpr std::array assets = {
    TextureAsset{chess::PieceType::Pawn, chess::Colour::White, "assets/PawnW.png"},
    TextureAsset{chess::PieceType::Pawn, chess::Colour::Black, "assets/PawnB.png"},
    TextureAsset{chess::PieceType::Knight, chess::Colour::White, "assets/KnightW.png"},
    TextureAsset{chess::PieceType::Knight, chess::Colour::Black, "assets/KnightB.png"},
    TextureAsset{chess::PieceType::Bishop, chess::Colour::White, "assets/BishopW.png"},
    TextureAsset{chess::PieceType::Bishop, chess::Colour::Black, "assets/BishopB.png"},
    TextureAsset{chess::PieceType::Rook, chess::Colour::White, "assets/RookW.png"},
    TextureAsset{chess::PieceType::Rook, chess::Colour::Black, "assets/RookB.png"},
    TextureAsset{chess::PieceType::Queen, chess::Colour::White, "assets/QueenW.png"},
    TextureAsset{chess::PieceType::Queen, chess::Colour::Black, "assets/QueenB.png"},
    TextureAsset{chess::PieceType::King, chess::Colour::White, "assets/KingW.png"},
    TextureAsset{chess::PieceType::King, chess::Colour::Black, "assets/KingB.png"},
};

constexpr auto light = sf::Color{235, 236, 208};
constexpr auto dark = sf::Color{115, 149, 82};
constexpr auto square_size = 100.0f;
constexpr auto icon_size = square_size * 0.8f;
const auto selected_square_outline = 2.0f;

sf::Vector2f square_position(chess::Position position, const chess::Board &board);

}
