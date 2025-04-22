//
// Created by olbnf on 17/04/2025.
//

#ifndef COMBATMANAGER_H
#define COMBATMANAGER_H

#include "CombatInfo.h"
#include "Joueur.h"
#include "Entraineur.h"
#include "TypeManager.h"

namespace PokemonGame {

    class CombatManager {
    private:
        Joueur* player_ = nullptr;
        Entraineur* entraineur_ = nullptr;
        TypeManager& typeManager_;

        int playerPokemonIndex_;
        int opponentPokemonIndex_;

        [[nodiscard]] static int findFirstPokemonAvailable(const Entraineur* trainer);

    public:
        CombatManager();
        ~CombatManager() = default;

        [[nodiscard]] bool startCombat(Joueur* player, Entraineur* opponent);
        [[nodiscard]] int checkCombatEnd() const;
        [[nodiscard]] static bool trainerKO(Entraineur* trainer) ;
        [[nodiscard]] TurnInfo playerTurn();
        [[nodiscard]] TurnInfo opponentTurn();
        [[nodiscard]] CombatPokemonInfo getCombatPokemonInfo(bool player = true) const;
    };

} // PokemonGame

#endif //COMBATMANAGER_H
