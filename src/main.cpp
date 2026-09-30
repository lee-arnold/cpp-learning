#include "chess/board.h"
#include "chess/moves/normal.h"
#include "chess/position.h"
#include "gui/window.h"
#include "terminal/board_printer.h"
#include "terminal/clear.h"
#include "terminal/input.h"

int main() {
    chess::Board board{};
    gui::Window window{board};

    terminal::BoardPrinter printer{board};

    while (window.is_open()) {
        window.process_events();

        if (!window.is_open()) break;

        window.clear();
        window.draw();
    }

    while (false) {
        terminal::clear();
        printer.print();

        auto requested_move = terminal::get_move_from_user();

        if (!requested_move) break;

        auto move{chess::NormalMove{requested_move->from, requested_move->to}};

        move.execute(board);
    }

    return 0;
}
