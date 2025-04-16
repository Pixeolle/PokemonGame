//
// Created by olbnf on 17/04/2025.
//

#ifndef MENU_H
#define MENU_H

#include <memory>
#include <string>
#include <unordered_map>

#include "CombatManager.h"
#include "DataLoader.h"
#include "Joueur.h"
#include "Leader.h"
#include "Maitre.h"


namespace PokemonGame {

    class Menu {
    private:
        std::unique_ptr<Joueur> player_;
        std::vector<std::unique_ptr<Leader>> leaders_;
        std::vector<std::unique_ptr<Maitre>> maitres_;
        std::unordered_map<std::string, std::unique_ptr<Pokemon>> pokemons_;
        CombatManager combatManager_;
        DataLoader dataLoader_;
        TypeManager* typeManager_ = nullptr;

        void loadData();

    public:
        Menu();
        ~Menu();

        void run();
    };

} // PokemonGame

#endif //MENU_H
