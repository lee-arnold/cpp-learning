#pragma once

#include "chess/board.h"
#include "chess/colour.h"
#include "chess/moves/move.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include "gui/texture.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <map>
#include <optional>
#include <utility>
#include <vector>

namespace gui {

struct RequestedMove {
    chess::Position from;
    chess::Position to;
};

class Window {
  public:
    Window(const chess::Board &board);
    void clear();
    void draw();
    std::optional<RequestedMove> process_events();
    bool is_open() const;
    void set_move_highlights(const std::vector<chess::Position> &positions);
    std::optional<chess::Position> selected_square() const;

  private:
    sf::RenderWindow window_;
    const chess::Board &board_;
    using TextureKey = std::pair<chess::PieceType, chess::Colour>;
    std::map<TextureKey, Texture> textures_;

    std::optional<chess::Position> selected_square_;
    std::vector<chess::Position> move_highlights_;

    void draw_square(chess::Position position);
    void draw_piece(chess::Position position);
    void draw_selected_square(chess::Position position);
    void draw_move_highlights(chess::Position position);
    void clear_move_highlights();
};

}
