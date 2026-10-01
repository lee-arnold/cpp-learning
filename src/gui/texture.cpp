#include "texture.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace gui {

Texture::Texture(const std::string filename) : texture_{filename} {
}

sf::Sprite Texture::get_sprite() const {
    return sf::Sprite{texture_};
}

}
