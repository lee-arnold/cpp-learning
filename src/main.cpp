#include "gui/game_controller.h"
#include "gui/window.h"
#include <exception>
#include <iostream>

int main() {
    try {
        gui::GameController game{};
        auto &window = game.window();

        while (window.is_open()) {
            game.process_events();

            if (!window.is_open()) break;
            window.clear();
            game.draw();
        }

        return 0;
    } catch (const std::exception &e) {
        std::cerr << e.what() << "\n";
        return 1;
    }
}
