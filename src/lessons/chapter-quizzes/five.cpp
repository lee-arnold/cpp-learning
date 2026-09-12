#include "lessons/chapter-quizzes/five.h"
#include <iostream>
#include <print>
#include <string>
#include <string_view>

std::string get_name(int num) {
    std::println("Enter the name of person #{}: ", num);
    std::string name{};
    std::getline(std::cin >> std::ws, name);

    return name;
}

int get_age(std::string_view name) {
    std::println("Enter the age of {}:", name);
    int age{};
    std::cin >> age;

    return age;
}

void run_quiz_5_question_4() {
    const std::string name1{get_name(1)};
    const int age1{get_age(name1)};
    const std::string name2{get_name(2)};
    const int age2{get_age(name2)};

    if (age1 > age2) {
        std::println("{} (age {}) is older than {} (age {}).", name1, age1, name2, age2);
    } else if (age2 > age1) {
        std::println("{} (age {}) is older than {} (age {}).", name2, age2, name1, age1);
    } else {
        std::println("{} and {} are the same age! (age {})", name1, name2, age1);
    }
}
