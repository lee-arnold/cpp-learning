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
            window.process_events();

            if (!window.is_open()) break;

            window.clear();
            window.draw();
        }

        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
