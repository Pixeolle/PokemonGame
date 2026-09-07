#include <iostream>

#ifdef _WIN32
    #include <windows.h>
#endif

#include "Menu.h"
#include "Utils.h"

using namespace PokemonGame;

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    Menu menu{};
}