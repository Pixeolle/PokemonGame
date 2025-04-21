//
// Created by olbnf on 19/04/2025.
//

#ifndef COMBATINFO_H
#define COMBATINFO_H

#include <string>
#include <vector>
struct CombatPokemonInfo {
    std::string name;
    int currentHp;
    int maxHp;
};

struct TurnInfo {
    CombatPokemonInfo playerPokemon;
    CombatPokemonInfo opponentPokemon;
    std::vector<std::string> messages;
};


#endif //COMBATINFO_H
