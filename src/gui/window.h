#pragma once

#include "chess/board.h"
#include "chess/colour.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include "gui/texture.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include <utility>

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
    using TextureKey = std::pair<chess::PieceType, chess::Colour>;
    std::map<TextureKey, Texture> textures_;
    void draw_square(chess::Position position);
    void draw_piece(chess::Position position);
};

}
