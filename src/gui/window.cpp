#include "window.h"
#include "chess/board.h"
#include "chess/utils.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowEnums.hpp>
#include <optional>

namespace {

constexpr auto light = sf::Color{235, 236, 208};
constexpr auto dark = sf::Color{115, 149, 82};
constexpr auto square_size = 100.0f;

}

namespace gui {

Window::Window(const chess::Board &board)
    : window_{sf::VideoMode{{800, 800}}, "Chess", sf::Style::Titlebar | sf::Style::Close},
      board_{board} {
}

bool Window::is_open() const {
    return window_.isOpen();
}

void Window::clear() {
    window_.clear();
}

void Window::draw() {
    for (int rank = board_.dimension(); rank-- > 0;) {
        for (int file = 0; file < board_.dimension(); ++file) {
            auto rect = sf::RectangleShape{};
            rect.setSize(sf::Vector2f(square_size, square_size));
            rect.setFillColor(chess::is_even(rank + file) ? dark : light);

            auto x = square_size * static_cast<float>(file);
            auto y = static_cast<float>(board_.dimension() - 1 - rank) * square_size;

            rect.setPosition({x, y});
            window_.draw(rect);
        }
    }

    window_.display();
}

void Window::process_events() {
    while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window_.close();
    }
}

}
