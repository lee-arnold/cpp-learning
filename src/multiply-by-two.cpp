#include "./multiply-by-two.hpp"
#include <iostream>

void multiply_by_two() {
    std::cout << "Enter an integer: " << std::endl;

    int num{};
    std::cin >> num;

    std::cout << "Double that number is: " << num * 2 << std::endl;
}
