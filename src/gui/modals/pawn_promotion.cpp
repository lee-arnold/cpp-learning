#include "gui/modals/pawn_promotion.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/direction.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include "gui/modals/modal.h"
#include "gui/utils.h"
#include "gui/window.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Angle.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>
#include <array>
#include <cstddef>
#include <optional>

namespace gui {

PawnPromotionModal::PawnPromotionModal(const chess::Board &board, Window &window)
    : Modal(),
      board_{board},
      window_{window},
      position_{},
      colour_{} {
}

void PawnPromotionModal::open(chess::Position position, chess::Colour colour) {
    toggle();
    position_ = position;
    colour_ = colour;
}

void PawnPromotionModal::draw(sf::RenderTarget &target) {
    if (!position_ || !colour_) return;
    auto position = *position_;

    for (size_t i = 0; i < elements_.size(); i++) {
        auto square_pos =
            square_position(position + chess::Direction::South() * static_cast<int>(i), board_);

        auto rect = sf::RectangleShape{};
        rect.setSize(sf::Vector2f(square_size, square_size));
        rect.setFillColor(sf::Color::White);
        rect.setPosition(square_pos);
        target.draw(rect);

        auto sprite = elements_[i].sprite;

        auto sprite_bounds = sprite.getLocalBounds();
        auto sprite_center = sf::Vector2f{
            sprite_bounds.position.x + sprite_bounds.size.x / 2.0f,
            sprite_bounds.position.y + sprite_bounds.size.y / 2.0f,
        };

        auto scale = icon_size / std::max(sprite_bounds.size.x, sprite_bounds.size.y);

        auto square_center = sf::Vector2f{
            square_pos.x + square_size / 2.0f,
            square_pos.y + square_size / 2.0f,
        };

        sprite.setOrigin(sprite_center);
        sprite.setPosition(square_center);
        sprite.setScale({scale, scale});
        target.draw(sprite);
    }

    const auto close_position = square_position(position + chess::Direction::South() * 4, board_);
    auto rect = sf::RectangleShape{};
    rect.setSize(sf::Vector2f(square_size, square_size / 2));
    rect.setFillColor(sf::Color(234, 234, 234));
    rect.setPosition(close_position);
    target.draw(rect);

    constexpr auto stroke_length = square_size * 0.15f;
    constexpr auto stroke_thickness = 2.0f;
    auto stroke = sf::RectangleShape{{stroke_length, stroke_thickness}};
    stroke.setFillColor(sf::Color(70, 70, 70));
    stroke.setOrigin({stroke_length / 2.0f, stroke_thickness / 2.0f});
    stroke.setPosition(close_position + sf::Vector2f{square_size / 2.0f, square_size / 4.0f});

    stroke.setRotation(sf::degrees(45.0f));
    target.draw(stroke);
    stroke.setRotation(sf::degrees(-45.0f));
    target.draw(stroke);
}

std::optional<chess::PieceType> PawnPromotionModal::handle_click(
    sf::Vector2i mouse_position [[maybe_unused]]
) {
    return chess::PieceType::Knight;
    // return std::nullopt;
}

}
