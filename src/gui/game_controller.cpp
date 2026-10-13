#include "gui/game_controller.h"
#include "chess/board.h"
#include "chess/colour.h"
#include "chess/game_state.h"
#include "chess/moves/move.h"
#include "chess/position.h"
#include "gui/window.h"
#include "utils.h"
#include <SFML/Window/Event.hpp>
#include <algorithm>
#include <memory>
#include <optional>

namespace gui {

GameController::GameController()
    : board_{chess::Board{}},
      game_state_{chess::GameState{chess::Colour::White, board_}},
      window_{board_} {
}

Window &GameController::window() {
    return window_;
}

void GameController::process_events() {
    while (const std::optional event = window_.window().pollEvent()) {
        handle_event(*event);
    }
}

void GameController::handle_event(const sf::Event &event) {
    // OS events
    if (event.is<sf::Event::Closed>()) window_.close();

    // Mouse events
    if (const auto *mouse = event.getIf<sf::Event::MouseButtonReleased>()) {
        if (mouse->position.x < 0 || mouse->position.y < 0) return;

        // @TODO check if any modals are open and handle those clicks
        auto position = get_board_position_from_click(mouse->position.x, mouse->position.y);
        if (!chess::Board::is_inside(position)) return;
        handle_board_click(position);
    }
}

void GameController::handle_board_click(const chess::Position &position) {
    if (!selected_square_) {
        // @TODO these need to be legal moves, not just available
        auto moves = game_state_.available_moves_for_piece(position);

        if (!moves.empty()) {
            selected_square_ = position;
            window_.set_move_highlights(moves);
        }
    } else {
        auto moves = game_state_.available_moves_for_piece(*selected_square_);

        const auto matches_destination = [&position](const auto &move) {
            return move->to() == position;
        };

        auto move = std::ranges::find_if(moves, matches_destination);

        // @TODO check and handle pawn promotion
        if (move != moves.end()) {
            handle_move(**move);
        }

        selected_square_ = std::nullopt;
        window_.clear_move_highlights();
    }
}

void GameController::handle_move(const chess::Move &move) {
    game_state_.execute_move(move);
    // @TODO check game over
}

chess::Position GameController::get_board_position_from_click(int mouse_x, int mouse_y) {
    auto square = static_cast<int>(square_size);

    auto file = mouse_x / square;
    auto rank = 7 - (mouse_y / square);

    return chess::Position{rank, file};
}

void GameController::draw() {
    window_.draw(selected_square_);
}

}
