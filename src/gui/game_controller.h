#pragma once

#include "chess/board.h"
#include "chess/game_state.h"
#include "chess/moves/move.h"
#include "chess/moves/pawn_promotion.h"
#include "chess/pieces/piece_type.h"
#include "chess/position.h"
#include "gui/modals/pawn_promotion.h"
#include "gui/window.h"
#include <SFML/Window/Event.hpp>
#include <optional>

namespace gui {

struct PendingPromotion {
    chess::Position from;
    chess::Position to;
};

class GameController {
  public:
    GameController();

    Window &window();

    void draw();
    void process_events();
    void handle_event(const sf::Event &event);
    void handle_move(const chess::Move &move);
    void handle_promotion(const chess::PieceType piece_type);
    void handle_board_click(const chess::Position &position);
    chess::Position get_board_position_from_click(int mouse_x, int mouse_y);

  private:
    chess::Board board_;
    chess::GameState game_state_;
    Window window_;
    PawnPromotionModal pawn_promotion_modal_;

    std::optional<PendingPromotion> pending_promotion_;
    std::optional<chess::Position> selected_square_;
};

}
