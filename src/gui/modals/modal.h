#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

namespace gui {

class Modal {
  public:
    virtual void draw(sf::RenderTarget &target) = 0;
    virtual ~Modal() = default;
    bool is_visible();
    void toggle();

  protected:
    Modal();

  private:
    bool is_visible_;
};

}
