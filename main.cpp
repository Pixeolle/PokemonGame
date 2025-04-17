#include <iostream>
#include <windows.h>

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    auto lang = "C++";
    std::cout << "Hello and welcome to et Bonjour a tout éùaê  " << lang << "!\n";

    for (int i = 1; i <= 5; i++) {
        std::cout << "i = " << i << std::endl;
    }

    return 0;
}