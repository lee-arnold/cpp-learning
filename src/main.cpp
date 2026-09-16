#include "chess/board.h"
#include "chess/moves/normal.h"
#include "chess/position.h"

int main() {
    chess::Board board{};

    auto move{chess::NormalMove{chess::Position{1, 1}, chess::Position{3, 1}}};

    move.execute(board);

    board.print();

    return 0;
}
