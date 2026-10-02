#include "texture.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <format>
#include <stdexcept>
#include <string_view>

namespace gui {

Texture::Texture(const std::string_view filename) : texture_{} {
    if (!texture_.loadFromFile(filename)) {
        throw std::runtime_error(std::format("Failed to load texture: {}", filename));
    }
}

sf::Sprite Texture::get_sprite() const {
    return sf::Sprite{texture_};
}

}
