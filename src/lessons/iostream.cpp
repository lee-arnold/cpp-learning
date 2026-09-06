#include "iostream.h"
#include <iostream>

int iostream() {
    int x{5};

    // the insertion operator << can be used multiple times to concatenate data
    std::cout << "x is equal to: " << x;

    std::cout << "Hi!" << std::endl; // std::endl will cause the cursor to move to the next line
    std::cout << "My name is Lee." << std::endl;

    // std::cout is buffered. This means the output can sit temporarily in the buffer and won't
    // necessarily appear immediately.
    // std::endl vs \n - std::endl flushes the buffer, while \n does not

    std::cout << "Yep." << '\n';
    std::cout << "And that's all, folks!\n";

    // note - single quotes ' are for single characters, double quotes " are for strings
    // the \n above is interpreted as a single character, thus single quotes

    std::cout << "Enter a number: ";

    int y{};
    std::cin >> y;

    std::cout << "You entered " << y << '\n';

    std::cout << "Enter two numbers separated by a space: ";

    int a{};
    std::cin >> a;

    int b{};
    std::cin >> b; // the extraction operator >> can be used multiple times to read multiple
                   // inputs, separated by whitespace

    std::cout << "You entered " << a << " and " << b << '\n';

    // std::cin is buffered. In the above example you can ignore the instructions and it will wait
    // for the next number to enter the buffer before proceeding. If you enter "3 4", it will read 3
    // into a and 4 into b, and then proceed.

    return 0;
}
