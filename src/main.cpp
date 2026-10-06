#include "chess/board.h"
#include "chess/game_state.h"
#include "chess/moves/move.h"
#include "chess/position.h"
#include "gui/window.h"
#include <algorithm>
#include <exception>
#include <iostream>
#include <memory>
#include <vector>

int main() {
    try {
        chess::Board board{};
        chess::GameState game_state{board};
        gui::Window window{board};

        while (window.is_open()) {
            auto requested_move = window.process_events();
            if (!window.is_open()) break;

            auto selected_square = window.selected_square();

            if (selected_square) {
                window.set_move_highlights(game_state.legal_moves_for_piece(*selected_square));
            }

            if (requested_move) {
                auto legal_moves = game_state.legal_moves_for_piece(requested_move->from);

                const auto matches_destination = [&requested_move](const auto &move) {
                    return move->to() == requested_move->to;
                };

                auto move = std::ranges::find_if(legal_moves, matches_destination);

                if (move != legal_moves.end()) {
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
