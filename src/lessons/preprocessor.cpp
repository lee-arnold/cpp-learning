// Preprocessor directives start with a # and end with a newline - NO semicolon
// These tell the preprocessor to perform certain text manipulation tasks

// #include - preprocessor replaces the directive with the contents of the included file

// #define - create a macro which defines how input text is converted into output text
// - 2 main types - object-like and function-type

// #include <iostream>
// #define MY_NAME "Lee"
//
// int main() {
//     std::cout << "My name is: " << MY_NAME << std::endl;
//     return 0;
// }

// the preprocessor converts the file:
// - adds the contents of iostream to the top of the file
// - inserts "Lee" in place of MY_NAME

// conditional compilation

// #ifdef, #ifndef, #if defined(var) and if !defined(var) can change compilation
// this can be used for build time branching, e.g. NODE_ENV=development
// it's commonly used for platform specific code or enabling optional diagnostics
//
// anything between #if 0 and #endif will not be compiled

// #include <iostream>
// #define PRINT_JOE
//
// int main() {
// #ifdef PRINT_JOE
//     std::cout << "Joe\n";
// #endif
//
// #ifdef PRINT_BOB
//     std::cout << "Bob\n";
// #endif
//
// #if 0
//     std::cout << "Won't be compiled"
// #endif
//
//     return 0;
// }
//
// Macro substitution does not work with other preprocessor commands
//
// #define FOO 9
// #ifdef FOO // This FOO does not get replaced with 9 because it’s part of another preprocessor
// std::cout << FOO << '\n'; // This FOO gets replaced with 9 because it's part of the normal code
// #endif
