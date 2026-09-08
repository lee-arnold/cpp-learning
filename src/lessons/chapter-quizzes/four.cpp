#include "lessons/chapter-quizzes/four.h"
#include <iostream>
#include <print>

double get_double_from_user() {
    double num{};
    std::println("Enter a double value: ");
    std::cin >> num;

    return num;
}

char get_operator_from_user() {
    char op{};
    std::println("Enter +, -, *, or /: ");
    std::cin >> op;

    return op;
}

double calculate(double num1, double num2, char op) {
    double output{};

    if (op == '+') {
        output = num1 + num2;
    } else if (op == '-') {
        output = num1 - num2;
    } else if (op == '*') {
        output = num1 * num2;
    } else if (op == '/') {
        output = num1 / num2;
    } else {
        std::println("Invalid operator.");
    }

    return output;
}

void run() {
    double num1{get_double_from_user()};
    double num2{get_double_from_user()};
    char op{get_operator_from_user()};

    double output{calculate(num1, num2, op)};

    std::println("Result: {}", output);
}
