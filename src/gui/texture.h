#pragma once

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>

namespace gui {

class Texture {
  public:
    Texture(const std::string filename);

    sf::Sprite get_sprite() const;

  private:
    sf::Texture texture_;
};

}
