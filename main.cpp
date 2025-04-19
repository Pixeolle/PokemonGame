#include <iostream>
#include <windows.h>

#include "DataLoader.h"
#include "Pokemon.h"

using namespace PokemonGame;

int main() {
    #ifdef _WIN32
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif

    std::string pokemonFilePath = "C:\\Users\\olbnf\\Downloads\\pokemon.csv";
    std::string joueurFilePath = "C:\\Users\\olbnf\\Downloads\\joueur.csv";
    std::string leaderFilePath = "C:\\Users\\olbnf\\Downloads\\leaders.csv";
    std::string maitreFilePath = "C:\\Users\\olbnf\\Downloads\\maitres.csv";
    std::string typeManagerFilePath = "C:\\Users\\olbnf\\Downloads\\typeMatrixPokemon.csv";

    DataLoader dataLoader(pokemonFilePath, joueurFilePath, leaderFilePath, maitreFilePath, typeManagerFilePath);

    std::unordered_map<std::string, std::unique_ptr<Pokemon>> mapPokemon = dataLoader.loadPokemon();


    /*std::cout << "--- Liste des pokémons ---" << std::endl;
    for (const auto& pair : mapPokemon) {
        pair.second->displayInfo();
    }*/

    std::unique_ptr<Joueur> player = dataLoader.loadJoueur(mapPokemon);

    player->displayStats();
    player->displayTeam();

    std::cout << std::endl;

    std::vector<std::unique_ptr<Leader>> leaders = dataLoader.loadLeader(mapPokemon);

    for (const auto& leader : leaders) {
        leader->displayInfo();
        leader->displayTeam();
    }

    std::cout << std::endl;
    std::vector<std::unique_ptr<Maitre>> maitres = dataLoader.loadMaitre(mapPokemon);

    for (const auto& maitre : maitres) {
        maitre->displayTeam();
    }

    std::cout << std::endl;

    auto& typeManager = TypeManager::getInstance();
    dataLoader.loadTypeMultipliers(typeManager);

    typeManager.displayMultiplierMatrix();
}