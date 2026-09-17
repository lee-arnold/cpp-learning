#include "board_printer.h"
#include "chess/board.h"
#include "chess/utils.h"
#include <cstddef>
#include <iostream>
#include <print>

namespace terminal {

void BoardPrinter::print() const {
    constexpr auto PIECE_COLOUR = "\x1b[38;2;38;36;33m";
    constexpr auto LIGHT_SQUARE = "\x1b[48;2;235;236;208m";
    constexpr auto DARK_SQUARE = "\x1b[48;2;115;149;82m";
    constexpr auto RESET = "\x1b[0m";
    constexpr auto EMPTY_CHAR = "  ";

    std::println("Printing the board:");

    for (int rank = board_.dimension(); rank-- > 0;) {
        for (int file = 0; file < board_.dimension(); ++file) {
            const auto background = chess::is_even(rank + file) ? DARK_SQUARE : LIGHT_SQUARE;

            std::cout << background;

            if (board_[rank][static_cast<std::size_t>(file)]) {
                std::cout << PIECE_COLOUR << board_[rank][static_cast<std::size_t>(file)]->icon()
                          << ' ';
            } else {
                std::cout << EMPTY_CHAR;
            }

            std::cout << RESET;
        }
        std::cout << '\n';
    }
}

}
