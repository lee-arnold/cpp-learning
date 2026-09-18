#include "clear.h"
#include <iostream>

namespace terminal {

void clear() {
    std::cout << "\033[2J\033[H";
}

}
