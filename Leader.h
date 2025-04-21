//
// Created by olbnf on 16/04/2025.
//

#ifndef LEADER_H
#define LEADER_H

#include <string>

#include "Entraineur.h"
#include "Interagir.h"

namespace PokemonGame {

    class Leader final : public Interagir, public Entraineur {
    private:
        const std::string badge_;
        const std::string gymnase_;
        bool isDefeated_ = false;

    public:
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
