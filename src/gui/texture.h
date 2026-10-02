#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string_view>

namespace gui {

class Texture {
  public:
    Texture(const std::string_view filename);

    sf::Sprite get_sprite() const;

  private:
    sf::Texture texture_;
};

}
