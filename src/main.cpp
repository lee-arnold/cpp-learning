#include "chess/board.h"
#include "chess/moves/normal.h"
#include "gui/window.h"
#include <exception>
#include <iostream>

int main() {
    try {
        chess::Board board{};
        gui::Window window{board};

        while (window.is_open()) {
            auto requested_move = window.process_events();
            if (!window.is_open()) break;

            if (requested_move) {
                auto move{chess::NormalMove{requested_move->from, requested_move->to}};
                move.execute(board);
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
