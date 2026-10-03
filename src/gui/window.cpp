#include "window.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/moves/move.h"
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
#include <array>
#include <memory>
#include <optional>
#include <string_view>
#include <vector>

namespace {

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

sf::Vector2f square_position(chess::Position position, const chess::Board &board) {
    auto x = square_size * static_cast<float>(position.file());
    auto y = static_cast<float>(board.dimension() - 1 - position.rank()) * square_size;

    return sf::Vector2f{x, y};
}

chess::Position to_position(int mouse_x, int mouse_y) {
    auto square = static_cast<int>(square_size);

    auto file = mouse_x / square;
    auto rank = 7 - (mouse_y / square);

    return chess::Position{rank, file};
}

}

namespace gui {

Window::Window(const chess::Board &board)
    : window_{sf::VideoMode{{800, 800}}, "Chess", sf::Style::Titlebar | sf::Style::Close},
      board_{board} {
    window_.setFramerateLimit(60);

    for (const auto &asset : assets) {
        textures_.try_emplace(TextureKey{asset.type, asset.colour}, asset.filename);
    }
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
            auto position = chess::Position{rank, file};

            draw_square(position);
            draw_piece(position);
            if (position == selected_square_) draw_selected_square(position);
            if (std::ranges::find(move_highlights_, position) != move_highlights_.end()) {
                draw_move_highlights(position);
            }
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
    if (board_.is_empty(position)) return;

    auto &piece = board_[position];

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

void Window::draw_selected_square(chess::Position position) {
    auto rect = sf::RectangleShape{};
    rect.setSize(sf::Vector2f(square_size, square_size));

    auto square_pos = square_position(position, board_);

    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(-selected_square_outline);
    rect.setOutlineColor(sf::Color::Red);
    rect.setPosition(square_pos);
    window_.draw(rect);
}

void Window::draw_move_highlights(chess::Position position) {
    auto rect = sf::RectangleShape{};
    rect.setSize(sf::Vector2f(square_size, square_size));

    auto square_pos = square_position(position, board_);

    rect.setFillColor(sf::Color::Transparent);
    rect.setOutlineThickness(-selected_square_outline);
    rect.setOutlineColor(sf::Color::Blue);
    rect.setPosition(square_pos);
    window_.draw(rect);
}

std::optional<chess::Position> Window::selected_square() const {
    return selected_square_;
}

void Window::set_move_highlights(std::vector<std::unique_ptr<chess::Move>> moves) {
    move_highlights_.reserve(moves.size());

    for (const auto &move : moves) {
        move_highlights_.push_back(move->to());
    }
}

void Window::clear_move_highlights() {
    move_highlights_.clear();
}

std::optional<RequestedMove> Window::process_events() {
    while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window_.close();
        if (const auto *mouse = event->getIf<sf::Event::MouseButtonReleased>()) {
            if (mouse->position.x < 0 || mouse->position.y < 0) continue;
            auto clicked_position = to_position(mouse->position.x, mouse->position.y);
            if (!chess::Board::is_inside(clicked_position)) continue;

            // selecting a piece
            if (!selected_square_ && !board_.is_empty(clicked_position)) {
                selected_square_ = clicked_position;
                continue;
            }

            // selecting a move
            if (selected_square_) {
                auto from = selected_square_;
                selected_square_ = std::nullopt;
                clear_move_highlights();

                return RequestedMove{
                    .from = *from,
                    .to = clicked_position,
                };
            }
        }
    }

    return std::nullopt;
}

}
