#pragma once

#include "chess/board.h"
#include "chess/colour.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include "gui/modals/modal.h"
#include "gui/window.h"
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/System/Vector2.hpp>
#include <array>
#include <optional>

namespace gui {

struct ModalElement {
    chess::PieceType piece_type;
    sf::Rect<float> rect;
    sf::Sprite sprite;
};

class PawnPromotionModal : public Modal {
  public:
    PawnPromotionModal(const chess::Board &board, Window &window);
    void draw(sf::RenderTarget &target) override;
    void open(chess::Position position, chess::Colour colour);
    std::optional<chess::PieceType> handle_click(sf::Vector2i mouse_position);

  private:
    const chess::Board &board_;
    Window &window_;
    std::optional<chess::Position> position_;
    std::optional<chess::Colour> colour_;
    std::array<ModalElement, 4> elements_ = {
        {{
             chess::PieceType::Queen,
             sf::Rect<float>{},
             window_.texture_for(chess::PieceType::Queen, *colour_),
         },
         {
             chess::PieceType::Knight,
             sf::Rect<float>{},
             window_.texture_for(chess::PieceType::Knight, *colour_),
         },
         {
             chess::PieceType::Rook,
             sf::Rect<float>{},
             window_.texture_for(chess::PieceType::Rook, *colour_),
         },
         {
             chess::PieceType::Bishop,
             sf::Rect<float>{},
             window_.texture_for(chess::PieceType::Bishop, *colour_),
         }}
    };
};

}
