#include "chess/board.h"
#include "chess/colour.h"
#include "chess/pieces/bishop.h"
#include "chess/pieces/king.h"
#include "chess/pieces/knight.h"
#include "chess/pieces/pawn.h"
#include "chess/pieces/piece.h"
#include "chess/pieces/queen.h"
#include "chess/pieces/rook.h"
#include "chess/position.h"

#include <array>
#include <cstddef>
#include <memory>

namespace chess {

Board::Board() {
    initialise();
}

void Board::initialise() {
    // Pawns
    for (std::size_t file = 0; file < 8; ++file) {
        board_[1][file] = std::make_unique<Pawn>(Colour::White);
        board_[6][file] = std::make_unique<Pawn>(Colour::Black);
    }

    // Rooks
    board_[0][0] = std::make_unique<Rook>(Colour::White);
    board_[0][7] = std::make_unique<Rook>(Colour::White);

    board_[7][0] = std::make_unique<Rook>(Colour::Black);
    board_[7][7] = std::make_unique<Rook>(Colour::Black);

    // Knights
    board_[0][1] = std::make_unique<Knight>(Colour::White);
    board_[0][6] = std::make_unique<Knight>(Colour::White);

    board_[7][1] = std::make_unique<Knight>(Colour::Black);
    board_[7][6] = std::make_unique<Knight>(Colour::Black);

    // Bishops
    board_[0][2] = std::make_unique<Bishop>(Colour::White);
    board_[0][5] = std::make_unique<Bishop>(Colour::White);

    board_[7][2] = std::make_unique<Bishop>(Colour::Black);
    board_[7][5] = std::make_unique<Bishop>(Colour::Black);

    // Queens
    board_[0][3] = std::make_unique<Queen>(Colour::White);
    board_[7][3] = std::make_unique<Queen>(Colour::Black);

    // Kings
    board_[0][4] = std::make_unique<King>(Colour::White);
    board_[7][4] = std::make_unique<King>(Colour::Black);
}

// this duplication is annoying. it can be neatened up with decltype
// but thats way too advanced for this simple project. maybe later

std::array<std::unique_ptr<Piece>, 8> &Board::operator[](int rank) {
    return board_[static_cast<std::size_t>(rank)];
}

const std::array<std::unique_ptr<Piece>, 8> &Board::operator[](int rank) const {
    return board_[static_cast<std::size_t>(rank)];
}

std::unique_ptr<Piece> &Board::operator[](Position position) {
    return board_[static_cast<std::size_t>(position.rank())]
                 [static_cast<std::size_t>(position.file())];
}

const std::unique_ptr<Piece> &Board::operator[](Position position) const {
    return board_[static_cast<std::size_t>(position.rank())]
                 [static_cast<std::size_t>(position.file())];
}

}
