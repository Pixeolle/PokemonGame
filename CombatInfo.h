//
// Created by olbnf on 19/04/2025.
//

#ifndef COMBATINFO_H
#define COMBATINFO_H

#include <string>
#include <vector>

enum class PlayerActionType {
    CHOOSE_MAIN_ACTION,
    ATTACK,
    SWITCH_POKEMON_ORDER,
    CHOOSE_FIRST_SWITCH_POKEMON_ORDER,
    CHOOSE_SECOND_SWITCH_POKEMON_ORDER,
    BACK
};

struct CombatPokemonInfo {
    std::string name;
    int currentHp;
    int maxHp;
};

struct CombatStateInfo {
    CombatPokemonInfo playerPokemon;
    CombatPokemonInfo opponentPokemon;
};

struct TurnInfo {
    std::vector<std::string> messages;
    bool combatEnded = false;
    std::string winnerName = "";
};

struct ActionRequestInfo {
    PlayerActionType actionType;
    std::vector<std::string> availableOptions;
    std::string promptMessage;
};

struct ChosenAction {
    PlayerActionType actionType;
    std::string choiceName = "";
};


#endif //COMBATINFO_H
