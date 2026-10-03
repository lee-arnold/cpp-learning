#include "chess/board.h"
#include "chess/game_state.h"
#include "chess/moves/normal.h"
#include "chess/position.h"
#include "gui/window.h"
#include <algorithm>
#include <exception>
#include <iostream>
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
                std::vector<chess::Position> legal_moves_to{};

                legal_moves_to.reserve(legal_moves.size());

                for (const auto &move : legal_moves) {
                    legal_moves_to.push_back(move->to());
                }

                if (std::ranges::find(legal_moves_to, requested_move->to) != legal_moves_to.end()) {
                    auto move{chess::NormalMove{requested_move->from, requested_move->to}};
                    move.execute(board);
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
