#include "lessons/chapter-quizzes/four.h"
#include <iostream>
#include <print>

// Question 2

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

void run_quiz_4_question_2() {
    double num1{get_double_from_user()};
    double num2{get_double_from_user()};
    char op{get_operator_from_user()};

    double output{calculate(num1, num2, op)};

    std::println("Result: {}", output);
}

// Question 3

void run_quiz_4_question_3() {
    double height{};
    double g{9.8};
    std::println("Enter the height of the tower in meters: ");
    std::cin >> height;

    for (double t = 0.0; t < 6.0; t++) {
        double fall_distance{g * (t * t) / 2.0};
        double ball_height{height - fall_distance};

        if (ball_height < 0) {
            std::println("At {} seconds, the ball is on the ground", t);
            return;
        }

        std::println("At {} seconds, the ball is at height: {} meters", t, ball_height);
    }
}
