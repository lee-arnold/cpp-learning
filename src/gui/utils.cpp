#include "gui/utils.h"
#include "chess/board.h"
#include "chess/position.h"
#include <SFML/System/Vector2.hpp>

namespace gui {

sf::Vector2f square_position(chess::Position position, const chess::Board &board) {
    auto x = gui::square_size * static_cast<float>(position.file());
    auto y = static_cast<float>(board.dimension() - 1 - position.rank()) * gui::square_size;

    return sf::Vector2f{x, y};
}

}
