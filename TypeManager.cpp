//
// Created by olbnf on 17/04/2025.
//

#include "TypeManager.h"

namespace PokemonGame {

    TypeManager::TypeManager() {}

    void TypeManager::loadMultipliers(std::unordered_map<Type, std::unordered_map<Type, float>>& multipliers) {
        multipliers_ = multipliers;
    }

    TypeManager& TypeManager::getInstance() {
        static TypeManager instance;
        return instance;
    }

    float TypeManager::getMultiplier(const std::vector<Type>& attackTypes, const std::vector<Type>& defenseTypes) const {
        float multiplier = 1.0f;

        for (auto& attaqueType : attackTypes) {

            const auto attackIterator = multipliers_.find(attaqueType);
            if (attackIterator != multipliers_.end()) {
                const auto& attackMultipliers = attackIterator->second;

                for (auto& defenseType : defenseTypes) {

                    const auto defenseIterator = attackMultipliers.find(defenseType);
                    if (defenseIterator != attackMultipliers.end()) {
                        multiplier *= defenseIterator->second;
                    }
                }
            }
        }
        return multiplier;
    }

} // PokemonGame