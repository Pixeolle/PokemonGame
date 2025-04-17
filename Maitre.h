//
// Created by olbnf on 16/04/2025.
//

#ifndef MAITRE_H
#define MAITRE_H

#include <string>

#include "Entraineur.h"

namespace PokemonGame {

    class Maitre final : public Interagir, public Entraineur{
    private:
        const float damageBonus_ = 0.25;
        bool isDefeated_ = false;

    public:
        explicit Maitre(std::string& name);
        ~Maitre() override = default;

        void setDefeated();
        void interact() const override;
        [[nodiscard]] bool canInteract() const override;

        [[nodiscard]] const float getDamageBonus() const;
    };

} // PokemonGame

#endif //MAITRE_H
