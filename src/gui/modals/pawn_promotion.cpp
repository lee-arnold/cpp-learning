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
#include <SFML/Graphics/Rect.hpp>
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
      window_{window} {
}

void PawnPromotionModal::open(chess::Position position, chess::Colour colour) {
    toggle();
    position_ = position;
    colour_ = colour;
    elements_ = {
        {{
             chess::PieceType::Queen,
             sf::FloatRect{},
             window_.texture_for(chess::PieceType::Queen, colour),
         },
         {
             chess::PieceType::Knight,
             sf::FloatRect{},
             window_.texture_for(chess::PieceType::Knight, colour),
         },
         {
             chess::PieceType::Rook,
             sf::FloatRect{},
             window_.texture_for(chess::PieceType::Rook, colour),
         },
         {
             chess::PieceType::Bishop,
             sf::FloatRect{},
             window_.texture_for(chess::PieceType::Bishop, colour),
         }}
    };

    int i = 0;
    for (auto &element : *elements_) {
        auto direction =
            colour == chess::Colour::Black ? chess::Direction::North() : chess::Direction::South();

        auto square_pos = square_position(position + direction * static_cast<int>(i), board_);

        element.rect = sf::FloatRect{square_pos, sf::Vector2f{square_size, square_size}};

        i++;
    }
}

void PawnPromotionModal::draw(sf::RenderTarget &target) {
    if (!position_ || !elements_) return;
    auto position = *position_;
    auto elements = *elements_;

    for (auto &element : *elements_) {
        auto square_pos = element.rect.position;

        auto rect = sf::RectangleShape{};
        rect.setSize(element.rect.size);
        rect.setFillColor(sf::Color::White);
        rect.setPosition(square_pos);
        target.draw(rect);

        auto sprite = element.sprite;

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

    const auto direction =
        colour_ == chess::Colour::Black ? chess::Direction::North() : chess::Direction::South();

    const auto close_position = square_position(position + direction * 4, board_);
    auto rect = sf::RectangleShape{};
    rect.setSize(sf::Vector2f(square_size, square_size));
    rect.setFillColor(sf::Color(234, 234, 234));
    rect.setPosition(close_position);
    target.draw(rect);

    auto stroke = sf::RectangleShape{{close_icon_stroke_length, close_icon_stroke_thickness}};
    stroke.setFillColor(sf::Color(70, 70, 70));
    stroke.setOrigin({close_icon_stroke_length / 2.0f, close_icon_stroke_thickness / 2.0f});
    stroke.setPosition(close_position + sf::Vector2f{square_size / 2.0f, square_size / 2.0f});

    stroke.setRotation(sf::degrees(45.0f));
    target.draw(stroke);
    stroke.setRotation(sf::degrees(-45.0f));
    target.draw(stroke);
}

std::optional<chess::PieceType> PawnPromotionModal::handle_click(sf::Vector2i mouse_position) {
    auto position = static_cast<sf::Vector2f>(mouse_position);

    for (const auto &element : *elements_) {
        if (element.rect.contains(position)) return element.piece_type;
    }

    return std::nullopt;
}

}
