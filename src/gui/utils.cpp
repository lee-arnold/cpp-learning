#include "gui/utils.h"
#include "chess/board.h"
#include "chess/position.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <algorithm>

namespace gui {

sf::Vector2f square_position(chess::Position position, const chess::Board &board) {
    auto x = square_size * static_cast<float>(position.file());
    auto y = static_cast<float>(board.dimension() - 1 - position.rank()) * square_size;

    return sf::Vector2f{x, y};
}

void fit_sprite_to_rect(sf::Sprite &sprite, sf::FloatRect rect) {
    auto sprite_bounds = sprite.getLocalBounds();
    auto sprite_center = sf::Vector2f{
        sprite_bounds.position.x + sprite_bounds.size.x / 2.0f,
        sprite_bounds.position.y + sprite_bounds.size.y / 2.0f,
    };

    auto scale = icon_fill_ratio *
                 std::min(rect.size.x / sprite_bounds.size.x, rect.size.y / sprite_bounds.size.y);

    auto square_center = sf::Vector2f{
        rect.position.x + rect.size.x / 2.0f,
        rect.position.y + rect.size.y / 2.0f,
    };

    sprite.setOrigin(sprite_center);
    sprite.setPosition(square_center);
    sprite.setScale({scale, scale});
}

}
