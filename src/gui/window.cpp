#include "window.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <algorithm>
#include <optional>

namespace {

constexpr auto light = sf::Color{235, 236, 208};
constexpr auto dark = sf::Color{115, 149, 82};
constexpr auto square_size = 100.0f;
constexpr auto icon_size = square_size * 0.8f;

sf::Vector2f square_position(chess::Position position, const chess::Board &board) {
    auto x = square_size * static_cast<float>(position.file());
    auto y = static_cast<float>(board.dimension() - 1 - position.rank()) * square_size;

    return sf::Vector2f{x, y};
}

}

namespace gui {

Window::Window(const chess::Board &board)
    : window_{sf::VideoMode{{800, 800}}, "Chess", sf::Style::Titlebar | sf::Style::Close},
      board_{board} {
    window_.setFramerateLimit(60);

    textures_.try_emplace(
        TextureKey{chess::PieceType::Pawn, chess::Colour::White},
        "assets/PawnW.png"
    );
    textures_.try_emplace(
        TextureKey{chess::PieceType::Pawn, chess::Colour::Black},
        "assets/PawnB.png"
    );
    textures_.try_emplace(
        TextureKey{chess::PieceType::Knight, chess::Colour::White},
        "assets/KnightW.png"
    );
    textures_.try_emplace(
        TextureKey{chess::PieceType::Knight, chess::Colour::Black},
        "assets/KnightB.png"
    );
    textures_.try_emplace(
        TextureKey{chess::PieceType::Bishop, chess::Colour::White},
        "assets/BishopW.png"
    );
    textures_.try_emplace(
        TextureKey{chess::PieceType::Bishop, chess::Colour::Black},
        "assets/BishopB.png"
    );
    textures_.try_emplace(
        TextureKey{chess::PieceType::Rook, chess::Colour::White},
        "assets/RookW.png"
    );
    textures_.try_emplace(
        TextureKey{chess::PieceType::Rook, chess::Colour::Black},
        "assets/RookB.png"
    );
    textures_.try_emplace(
        TextureKey{chess::PieceType::Queen, chess::Colour::White},
        "assets/QueenW.png"
    );
    textures_.try_emplace(
        TextureKey{chess::PieceType::Queen, chess::Colour::Black},
        "assets/QueenB.png"
    );
    textures_.try_emplace(
        TextureKey{chess::PieceType::King, chess::Colour::White},
        "assets/KingW.png"
    );
    textures_.try_emplace(
        TextureKey{chess::PieceType::King, chess::Colour::Black},
        "assets/KingB.png"
    );
}

bool Window::is_open() const {
    return window_.isOpen();
}

void Window::clear() {
    window_.clear();
}

void Window::draw() {
    for (int rank = board_.dimension(); rank-- > 0;) {
        for (int file = 0; file < board_.dimension(); ++file) {
            draw_square(chess::Position{rank, file});
            draw_piece(chess::Position{rank, file});
        }
    }

    window_.display();
}

void Window::draw_square(chess::Position position) {
    auto rect = sf::RectangleShape{};
    rect.setSize(sf::Vector2f(square_size, square_size));
    rect.setFillColor(position.squareColour() == chess::Colour::Black ? dark : light);

    auto square_pos = square_position(position, board_);

    rect.setPosition(square_pos);
    window_.draw(rect);
}

void Window::draw_piece(chess::Position position) {
    auto &piece = board_[position];
    if (!piece) return;

    auto sprite = textures_.at(TextureKey{piece->type(), piece->colour()}).get_sprite();
    auto sprite_bounds = sprite.getLocalBounds();
    auto sprite_center = sf::Vector2f{
        sprite_bounds.position.x + sprite_bounds.size.x / 2.0f,
        sprite_bounds.position.y + sprite_bounds.size.y / 2.0f,
    };

    auto scale = icon_size / std::max(sprite_bounds.size.x, sprite_bounds.size.y);

    auto square_pos = square_position(position, board_);
    auto square_center = sf::Vector2f{
        square_pos.x + square_size / 2.0f,
        square_pos.y + square_size / 2.0f,
    };

    sprite.setOrigin(sprite_center);
    sprite.setPosition(square_center);
    sprite.setScale({scale, scale});
    window_.draw(sprite);
}

void Window::process_events() {
    while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window_.close();
    }
}

}
