//
// Created by olbnf on 16/04/2025.
//

#ifndef POKEMON_H
#define POKEMON_H
#include <string>
#include <vector>

#include "Interagir.h"
#include "Types.h"

namespace PokemonGame {

    class Pokemon : public Interagir{
    private:
        const std::string name_;
        const int maxHp_;
        int hp_;
        const std::vector<Type> types_;
        const std::string attackName_;
        const int attackPower_;

    public:
        Pokemon(const std::string& name, int hp, const std::vector<Type>& types, const std::string& attackName, int attackPower);
        Pokemon(const Pokemon& other);
        ~Pokemon() override = default;

        void applyDamage(int damage);
        void heal(int amount);
        void displayInfo() const;
        [[nodiscard]] bool isFainted() const;
        void interact() const override;

        [[nodiscard]] const std::string& getName() const;
        [[nodiscard]] const int getMaxHp() const;
        [[nodiscard]] int getHp() const;
        [[nodiscard]] const std::vector<Type>& getTypes() const;
        [[nodiscard]] const std::string& getAttackName() const;
        [[nodiscard]] const int getAttackPower() const;
    };

} // PokemonGame

#endif //POKEMON_H
