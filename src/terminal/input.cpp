#include "terminal/input.h"
#include "chess/parsing.h"
#include <iostream>
#include <optional>
#include <string>

namespace terminal {

std::optional<RequestedMove> get_move_from_user() {
    std::cout << "Enter a move from/to: (e.g. a2 a4)\n";

    std::string from{};
    std::string to{};

    while (true) {
        if (!(std::cin >> from >> to)) {
            return std::nullopt;
        }

        if (!chess::is_valid_move_format(from) || !chess::is_valid_move_format(to)) {
            std::cout << "Invalid move format, try again:\n";
        } else {
            return RequestedMove{
                .from = chess::parse_position(from),
                .to = chess::parse_position(to),
            };
        }
    }
}

}
