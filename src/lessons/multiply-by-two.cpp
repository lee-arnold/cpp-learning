#include "./multiply-by-two.h"
#include <iostream>

int get_value_from_user() {
    std::cout << "Enter an integer: " << std::endl;

    // it's best practice to define variables closest to their first use, within reason
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
    // alternatively print_double(get_value_from_user());
}
