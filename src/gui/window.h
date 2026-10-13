#pragma once

#include "chess/board.h"
#include "chess/colour.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include "gui/texture.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include <memory>
#include <optional>
#include <utility>
#include <vector>

namespace gui {

class Window {
  public:
    explicit Window(const chess::Board &board);
    sf::RenderWindow &window();

    void close();
    void clear();
    void draw(std::optional<chess::Position> selected_square);

    bool is_open() const;
    void set_move_highlights(const std::vector<std::unique_ptr<chess::Move>> &moves);
    void clear_move_highlights();

  private:
    sf::RenderWindow window_;
    const chess::Board &board_;
    using TextureKey = std::pair<chess::PieceType, chess::Colour>;
    std::map<TextureKey, Texture> textures_;

    std::vector<chess::Position> move_highlights_;

    void draw_square(chess::Position position);
    void draw_piece(chess::Position position);
    void draw_selected_square(chess::Position position);
    void draw_move_highlights(chess::Position position);
};

}
