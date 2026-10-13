#pragma once

#include <concepts>

namespace chess {

constexpr bool is_even(std::integral auto num) {
    return num % 2 == 0;
}

}
