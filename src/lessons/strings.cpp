#include <iostream>
#include <string>

void run_strings() {
    std::cout << "Enter your full name: " << std::endl;
    std::string name{};
    std::getline(std::cin >> std::ws, name);

    std::cout << "Enter your age: " << std::endl;
    int age{};
    std::cin >> age;

    int sum{age + static_cast<int>(name.length())};

    std::cout << "Your age + length of name is: " << sum << std::endl;
}
