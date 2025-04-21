//
// Created by olbnf on 17/04/2025.
//

#include <iomanip>
#include <iostream>

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

        for (auto& attackType : attackTypes) {

            const auto attackIterator = multipliers_.find(attackType);
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

    void TypeManager::displayMultiplierMatrix() const {

        const std::vector<Type> displayOrder = {
            Type::NORMAL, Type::FEU, Type::EAU, Type::PLANTE, Type::ELECTRIK, Type::GLACE,
            Type::COMBAT, Type::POISON, Type::SOL, Type::VOL, Type::PSY, Type::INSECTE,
            Type::ROCHE, Type::SPECTRE, Type::DRAGON, Type::TENEBRES, Type::ACIER, Type::FEE
        };

        if (displayOrder.empty()) {
            std::cout << "Aucun type à afficher." << std::endl;
            return;
        }

        size_t firstColWidth = 0;
        size_t dataColWidth = 0;

        for (Type t : displayOrder) {
            firstColWidth = std::max(firstColWidth, typeToString(t).length());
            dataColWidth = std::max(dataColWidth, typeToString(t).length());
        }

        dataColWidth = std::max(dataColWidth, (size_t)5);
        firstColWidth += 2;
        dataColWidth += 2;

        std::cout << "Table des Types (Attaque \\ Défense)" << std::endl;


        std::cout << std::left << std::setw(firstColWidth) << " ";
        for (Type defenseType : displayOrder) {
            std::cout << std::left << std::setw(dataColWidth) << typeToString(defenseType);
        }
        std::cout << std::endl;

        std::cout << std::string(firstColWidth + dataColWidth * displayOrder.size(), '-') << std::endl;


        std::cout << std::fixed << std::setprecision(2);

        for (Type attackType : displayOrder) {
            std::cout << std::left << std::setw(firstColWidth) << typeToString(attackType);

            for (Type defenseType : displayOrder) {
                float multiplier = 1.0f;

                auto it_outer = multipliers_.find(attackType);
                if (it_outer != multipliers_.end()) {
                    const auto& innerMap = it_outer->second;
                    auto it_inner = innerMap.find(defenseType);
                    if (it_inner != innerMap.end()) {
                        multiplier = it_inner->second;
                    }
                }


                std::cout << std::left << std::setw(dataColWidth) << multiplier;
            }
            std::cout << std::endl;
        }
         std::cout << std::string(firstColWidth + dataColWidth * displayOrder.size(), '-') << std::endl;


         std::cout.unsetf(std::ios_base::floatfield);
         std::cout.precision(6);

    }

} // PokemonGame