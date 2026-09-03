#include <iostream>

int variables() {
    // older forms of initialisation
    int a; // default initialisation, value is indeterminate
    a = 5;

    int b = 10; // copy initialisation, inherited from C
    int c(10);  // direct initialisation, more efficient for complex objects

    // newer forms of initialisation
    int d{10}; // direct list initialisation, disallows narrowing conversions
    // int d{4.5}; // errors because double can't narrow to int

    int e{}; // value initialisation, initializes to zero for fundamental types

    std::cout << a;
    std::cout << b;
    std::cout << c;
    std::cout << d;
    std::cout << e;
    return 0;
}
