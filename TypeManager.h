//
// Created by olbnf on 17/04/2025.
//

#ifndef TYPEMANAGER_H
#define TYPEMANAGER_H

#include <unordered_map>
#include <vector>

#include "Types.h"

namespace PokemonGame {

    class TypeManager {
    private:
        static TypeManager* instance_;
        std::unordered_map<Type, std::unordered_map<Type, float>> multipliers_;

        TypeManager();
        ~TypeManager();

    public:
        void loadMultipliers(std::unordered_map<Type, std::unordered_map<Type, float>>& multipliers);
        [[nodiscard]] float getMultiplier(const std::vector<Type>& attackType, const std::vector<Type>& defenseType);

        [[nodiscard]] static TypeManager* getInstance();
    };

} // PokemonGame

#endif //TYPEMANAGER_H
