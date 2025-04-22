//
// Created by olbnf on 16/04/2025.
//

#ifndef LEADER_H
#define LEADER_H

#include <string>

#include "Entraineur.h"
#include "Interagir.h"

namespace PokemonGame {

    /**
     * classe Leader
     * @brief Représente un leader de gymnase dans le jeu Pokémon.
     * La classe Leader hérite des classes Interagir et Entraineur. Elle contient des informations
     * spécifiques à un leader, telles que le badge, le gymnase et l'état de défaite.
     */
    class Leader final : public Interagir, public Entraineur {
    private:
        const std::string badge_;
        const std::string gymnase_;
        bool isDefeated_ = false;

    public:
        /**
         * Constructeur de la classe Leader.
         * @param name Nom du leader.
         * @param badge Badge du leader.
         * @param gymnase Gymnase du leader.
         */
        Leader(const std::string& name, const std::string& badge, const std::string& gymnase);
        ~Leader() override = default;

        void defeated() override;
        void displayInfo() const;
        [[nodiscard]] std::string interact() const override;
        [[nodiscard]] bool canInteract() const override;

        [[nodiscard]] const std::string& getBadge() const;
        [[nodiscard]] const std::string& getGymnase() const;
    };

} // PokemonGame

#endif //LEADER_H
