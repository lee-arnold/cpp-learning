#include "chess/board.h"
#include "chess/game_state.h"
#include "chess/moves/move.h"
#include "chess/position.h"
#include "gui/window.h"
#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <optional>
#include <ranges>
#include <vector>

int main() {
    try {
        chess::Board board{};
        chess::GameState game_state{board};
        gui::Window window{board};
        std::optional<chess::Position> last_selected_square{};

        while (window.is_open()) {
            const auto requested_move = window.process_events();
            if (!window.is_open()) break;

            const auto selected_square = window.selected_square();

            if (selected_square && selected_square != last_selected_square) {
                const auto highlight_moves = game_state.available_moves_for_piece(*selected_square);
                const auto positions =
                    highlight_moves |
                    std::views::transform([](const auto &move) { return move->to(); }) |
                    std::ranges::to<std::vector>();

                window.set_move_highlights(positions);
            }

            last_selected_square = selected_square;

            if (requested_move) {
                auto available_moves = game_state.available_moves_for_piece(requested_move->from);

                const auto matches_destination = [&requested_move](const auto &move) {
                    return move->to() == requested_move->to;
                };

                auto move = std::ranges::find_if(available_moves, matches_destination);

                if (move != available_moves.end()) {
                    (*move)->execute(board);
                }
            }

            window.clear();
            window.draw();
        }

        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
