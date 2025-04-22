//
// Created by olbnf on 17/04/2025.
//

#ifndef TYPEMANAGER_H
#define TYPEMANAGER_H

#include <unordered_map>
#include <vector>

#include "Types.h"

namespace PokemonGame {

    /**
     * @class TypeManager
     * @brief Classe responsable de la gestion des multiplicateurs de types dans le jeu.
     * Cette classe implémente le pattern singleton pour garantir une instance unique.
     * Elle permet de charger, calculer et afficher les multiplicateurs de types.
     */
    class TypeManager {
    private:
        /**
         * @brief Contient les multiplicateurs de types.
         * La clé externe représente le type d'attaque, et la clé interne représente le type de défense
         * avec sa valeur associée (le multiplicateur).
         */
        std::unordered_map<Type, std::unordered_map<Type, float>> multipliers_;

        TypeManager() = default;
        ~TypeManager() = default;

        TypeManager(const TypeManager&) = delete;
        /**
         * @brief Opérateur d'affectation par copie supprimé pour éviter la duplication de l'instance.
         */
        TypeManager& operator=(const TypeManager&) = delete;
        TypeManager(TypeManager&&) = delete;
        TypeManager& operator=(TypeManager&&) = delete;

    public:
        /**
         * @brief Charge les multiplicateurs de types dans le gestionnaire.
         * @param multipliers Une map contenant les multiplicateurs de types.
         * La clé externe représente le type d'attaque, et la clé interne représente le type de défense
         * avec sa valeur associée (le multiplicateur).
         */
        void loadMultipliers(std::unordered_map<Type, std::unordered_map<Type, float>>& multipliers);

        /**
         * @brief Affiche la matrice des multiplicateurs de types sous forme de tableau.
         *
         * Cette méthode affiche les types d'attaque et de défense dans un tableau lisible,
         * avec les multiplicateurs correspondants.
         */
        void displayMultiplierMatrix() const;

        [[nodiscard]] static TypeManager& getInstance();
        [[nodiscard]] float getMultiplier(const std::vector<Type>& attackTypes, const std::vector<Type>& defenseTypes) const;
    };

} // PokemonGame

#endif //TYPEMANAGER_H
