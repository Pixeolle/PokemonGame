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
        std::unordered_map<Type, std::unordered_map<Type, float>> multipliers_;

        TypeManager();
        ~TypeManager() = default;

        TypeManager(const TypeManager&) = delete;
        TypeManager& operator=(const TypeManager&) = delete;
        TypeManager(TypeManager&&) = delete;
        TypeManager& operator=(TypeManager&&) = delete;

    public:
        void loadMultipliers(std::unordered_map<Type, std::unordered_map<Type, float>>& multipliers);
        void displayMultiplierMatrix() const;

        [[nodiscard]] static TypeManager& getInstance();
        [[nodiscard]] float getMultiplier(const std::vector<Type>& attackTypes, const std::vector<Type>& defenseTypes) const;
    };

} // PokemonGame

#endif //TYPEMANAGER_H
