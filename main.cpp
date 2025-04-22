#include <iostream>
#include <windows.h>

#include "Menu.h"
#include "Utils.h"

using namespace PokemonGame;

int main() {
    #ifdef _WIN32 /// permet de changer l'encodage de la console et donc de pouvoir afficher les caractères spéciaux
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    Menu menu{};
}