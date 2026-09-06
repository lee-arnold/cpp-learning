// anything that is not defined inside a class, funcction or namespace is considered part of the global scope
// therefore naming collisions can occur

// the below will cause a linker error, because get_value_from_user already exists in multiply_by_two
// note that we're not even using this function for the linker to error

// int get_value_from_user() {
//     std::cout << "Enter an integer: " << std::endl;
//
//     // it's best practice to define variables closest to their first use, within reason
//     int num{};
//     std::cin >> num;
//
//     return num;
// }

// std is a namespace. e.g. std::cout is the cout function from the std namespace
// :: is called the scope resolution operator

// DO NOT do the following. Any function we define could conflict with anything in std
// this is a misuse of using and defeats the point of namespaces

// #include <iostream>;
//
// using namespace std;
//
// int main() {
//     cout << "Hello world!";
//     return 0;
// }
