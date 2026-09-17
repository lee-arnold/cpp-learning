#include "chess/board.h"
#include "chess/moves/normal.h"
#include "chess/position.h"
#include "terminal/board_printer.h"

int main() {
    chess::Board board{};
    terminal::BoardPrinter printer{board};

    auto move{chess::NormalMove{chess::Position{1, 1}, chess::Position{3, 1}}};

    move.execute(board);

    printer.print();

    return 0;
}
