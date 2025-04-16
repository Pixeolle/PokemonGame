cmake_minimum_required(VERSION 3.30)
project(PokemonGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(PokemonGame main.cpp
        Types.h
        Pokemon.h
        Interagir.h
        Entraineur.h
        Joueur.cpp
        Joueur.h
        Maitre.cpp
        Maitre.h
        Leader.cpp
        Leader.h
        TypeManager.cpp
        TypeManager.h
        DataLoader.cpp
        DataLoader.h
        CombatManager.cpp
        CombatManager.h
        Menu.cpp
        Menu.h)
