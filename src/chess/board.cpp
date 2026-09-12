#include "board.h"
#include "chess/pieces/bishop.h"
#include "chess/pieces/king.h"
#include "chess/pieces/knight.h"
#include "chess/pieces/pawn.h"
#include "chess/pieces/queen.h"
#include "chess/pieces/rook.h"
#include "chess/utils.h"
#include "colour.h"

#include <cstddef>
#include <iostream>
#include <memory>
#include <print>

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

void Board::print() const {
    constexpr auto PIECE_COLOUR = "\x1b[38;2;38;36;33m";
    constexpr auto LIGHT_SQUARE = "\x1b[48;2;235;236;208m";
    constexpr auto DARK_SQUARE = "\x1b[48;2;115;149;82m";
    constexpr auto RESET = "\x1b[0m";
    constexpr auto EMPTY_CHAR = "  ";

    std::println("Printing the board:");

    for (std::size_t rank = board_.size(); rank-- > 0;) {
        for (std::size_t file = 0; file < board_[rank].size(); ++file) {
            const auto background = is_even(rank + file) ? DARK_SQUARE : LIGHT_SQUARE;

            std::cout << background;

            if (board_[rank][file]) {
                std::cout << PIECE_COLOUR << board_[rank][file]->icon() << ' ';
            } else {
                std::cout << EMPTY_CHAR;
            }

            std::cout << RESET;
        }
        std::cout << '\n';
    }
}

}
