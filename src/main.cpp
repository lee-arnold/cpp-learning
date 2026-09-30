#include "chess/board.h"
#include "chess/moves/normal.h"
#include "chess/position.h"
#include "terminal/board_printer.h"
#include "terminal/clear.h"
#include "terminal/input.h"

int main() {
    chess::Board board{};
    terminal::BoardPrinter printer{board};

    while (true) {
        terminal::clear();
        printer.print();

        auto requested_move = terminal::get_move_from_user();

        auto move{chess::NormalMove{requested_move.from, requested_move.to}};

        move.execute(board);
    }

    return 0;
}
