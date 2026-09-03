#include "./multiply-by-two.hpp"
#include <iostream>

int get_value_from_user() {
    std::cout << "Enter an integer: " << std::endl;

    int num{};
    std::cin >> num;

    return num;
}

void print_double(int num) {
    std::cout << "Double that number is: " << num * 2 << std::endl;
}

void multiply_by_two() {
    int num{get_value_from_user()};

    print_double(num);
}
