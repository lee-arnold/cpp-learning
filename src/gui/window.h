#pragma once

#include "chess/board.h"
#include <SFML/Graphics/RenderWindow.hpp>

namespace gui {

class Window {
  public:
    Window(const chess::Board &board);
    void clear();
    void draw();
    void process_events();
    bool is_open() const;

  private:
    sf::RenderWindow window_;
    const chess::Board &board_;
};

}
