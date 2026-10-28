#include "window.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include "gui/utils.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <algorithm>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace gui {

Window::Window(const chess::Board &board)
    : window_{sf::VideoMode{{800, 800}}, "Chess", sf::Style::Titlebar | sf::Style::Close},
      board_{board} {
    window_.setFramerateLimit(60);

    for (const auto &asset : assets) {
        textures_.try_emplace(TextureKey{asset.type, asset.colour}, asset.filename);
    }
}

sf::RenderWindow &Window::window() {
    return window_;
}

bool Window::is_open() const {
    return window_.isOpen();
}

void Window::close() {
    window_.close();
}

void Window::clear() {
    window_.clear();
}

void Window::draw(std::optional<chess::Position> selected_square) {
    for (int rank = board_.dimension(); rank-- > 0;) {
        for (int file = 0; file < board_.dimension(); ++file) {
            auto position = chess::Position{rank, file};

            draw_square(position);
            draw_piece(position);
            if (position == selected_square) draw_selected_square(position);
            if (std::ranges::find(move_highlights_, position) != move_highlights_.end()) {
                draw_move_highlights(position);
            }
        }
    }
}

void Window::display() {
    window_.display();
}

void Window::draw_square(chess::Position position) {
    auto rect = sf::RectangleShape{};
    rect.setSize(sf::Vector2f(square_size, square_size));
    rect.setFillColor(position.square_colour() == chess::Colour::Black ? dark : light);

    auto square_pos = square_position(position, board_);

    rect.setPosition(square_pos);
    window_.draw(rect);
}

void Window::draw_piece(chess::Position position) {
    if (!board_.is_inside(position) || board_.is_empty(position)) return;

    const auto *piece = board_[position];
    auto sprite = sprite_for(piece->type(), piece->colour());
    auto rect = sf::FloatRect{
        square_position(position, board_),
        sf::Vector2f{square_size, square_size},
    };

    fit_sprite_to_rect(sprite, rect);

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

void Window::set_move_highlights(const std::vector<std::unique_ptr<chess::Move>> &moves) {
    std::vector<chess::Position> positions;
    positions.reserve(moves.size());

    for (const auto &move : moves) {
        positions.push_back(move->to());
    }

    move_highlights_ = std::move(positions);
}

void Window::clear_move_highlights() {
    move_highlights_.clear();
}

sf::Sprite Window::sprite_for(chess::PieceType type, chess::Colour colour) const {
    return textures_.at(TextureKey{type, colour}).get_sprite();
}

}
