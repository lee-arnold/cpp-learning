#include "chess/board.h"
#include "chess/moves/normal.h"
#include "gui/window.h"

int main() {
    chess::Board board{};
    gui::Window window{board};

    while (window.is_open()) {
        window.process_events();

        if (!window.is_open()) break;

        window.clear();
        window.draw();
    }

    return 0;
}
