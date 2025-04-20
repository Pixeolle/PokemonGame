//
// Created by olbnf on 17/04/2025.
//

#ifndef COMBATMANAGER_H
#define COMBATMANAGER_H

#include "Joueur.h"
#include "Entraineur.h"
#include "TypeManager.h"

namespace PokemonGame {

    class CombatManager {
    private:
        Joueur* player_ = nullptr;
        Entraineur* entraineur_ = nullptr;
        TypeManager& typeManager_;

        void playerTurn();
        void oppoentTurn();
        [[nodiscard]] bool checkCombatEnd() const;

    public:
        explicit CombatManager(TypeManager& typeManager);
        ~CombatManager() = default;

        bool startCombat(Joueur* player, Entraineur* opponent);
    };

} // PokemonGame

#endif //COMBATMANAGER_H
