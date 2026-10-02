#include "texture.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string_view>

namespace gui {

Texture::Texture(const std::string_view filename) : texture_{filename} {
}

sf::Sprite Texture::get_sprite() const {
    return sf::Sprite{texture_};
}

}
