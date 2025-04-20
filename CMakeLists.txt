cmake_minimum_required(VERSION 3.30)
project(PokemonGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(PokemonGame main.cpp
        Types.h
        Types.cpp
        Interagir.h
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
        Menu.h
        Pokemon.cpp
        Pokemon.h
        Utils.cpp
        Utils.h
        Entraineur.cpp
        Entraineur.h
        CombatInfo.h
)

