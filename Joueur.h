//
// Created by olbnf on 16/04/2025.
//

#ifndef JOUEUR_H
#define JOUEUR_H

#include <set>
#include <string>

#include "Entraineur.h"

namespace PokemonGame {

    class Joueur final : public Entraineur {
    private:
        std::set<std::string> badges_;
        int wins_ = 0;
        int losses_ = 0;

    public:
        explicit Joueur(const std::string& name);
        ~Joueur() override = default;

        void addBadge(const std::string& badgeName);
        void addWin();
        void addLose();
        void displayStats() const;
        [[nodiscard]] bool canInteract() const override;

        [[nodiscard]] std::set<std::string>& getBadges() const;
        [[nodiscard]] int getWins() const;
        [[nodiscard]] int getLosses() const;
    };

} // PokemonGame

#endif //JOUEUR_H
