//
// Created by olbnf on 16/04/2025.
//

#ifndef MAITRE_H
#define MAITRE_H

#include <string>

#include "Entraineur.h"

namespace PokemonGame {

    /**
     * @brief La classe Maitre représente un maitre Pokémon.
    * La classe Maitre hérite des classes Interagir et Entraineur. Elle contient des informations
     * spécifiques à un maître, telles que le bonus de dégâts et l'état de défaite.
     */
    class Maitre final : public Interagir, public Entraineur{
    private:
        const float damageBonus_ = 0.25;
        bool isDefeated_ = false;

    public:
        /**
         * @brief Constructeur explicite de la classe Maitre.
         * @param name Nom du maître.
         */
        explicit Maitre(std::string& name);
        ~Maitre() override = default;

        void defeated() override;
        [[nodiscard]] std::string interact() const override;
        [[nodiscard]] bool canInteract() const override;

        [[nodiscard]] float getDamageBonus() const;
    };

} // PokemonGame

#endif //MAITRE_H
