#pragma once

#include <SFML/Graphics/RenderTarget.hpp>

namespace gui {

class Modal {
  public:
    virtual void draw(sf::RenderTarget &target) = 0;
    virtual ~Modal() = default;
    bool is_visible() const;
    void toggle();
    void show();
    void hide();

  protected:
    Modal();

  private:
    bool is_visible_;
};

}
