#include "window.h"
#include "chess/board.h"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <optional>

namespace gui {

Window::Window(const chess::Board &board)
    : window_{sf::VideoMode{{800, 600}}, "Chess"}, board_{board} {
}

bool Window::is_open() const {
    return window_.isOpen();
}

void Window::clear() {
    window_.clear();
}

void Window::update() {
    // draw stuff here
    window_.display();
}

void Window::process_events() {
    while (const std::optional event = window_.pollEvent()) {
        if (event->is<sf::Event::Closed>()) window_.close();
    }
}

}
