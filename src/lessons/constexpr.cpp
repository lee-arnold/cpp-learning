#include <iostream>

int five() {
    return 5;
};

constexpr int cmax(int x, int y) {
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

int nmax(int x, int y) {
    if (x < y) {
        return x;
    } else {
        return y;
    }
}

int run_constexpr() {
    constexpr double gravity [[maybe_unused]]{9.8};

    constexpr int sum{4 + 5};
    constexpr int something [[maybe_unused]]{sum};

    std::cout << "Enter your age: ";
    int age{};
    std::cin >> age;

    // both of these would cause a compiler error, because the variables are not
    // constant at compile time
    // constexpr int myAge{age};
    // constexpr int f{five()};

    constexpr int x [[maybe_unused]]{cmax(5, 6)};
    // this one errors because nmax is not a constexpr function
    // constexpr int y{nmax(5, 6)};

    return 0;
}
