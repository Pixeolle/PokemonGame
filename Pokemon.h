//
// Created by olbnf on 16/04/2025.
//

#ifndef POKEMON_H
#define POKEMON_H
#include <string>
#include <vector>
#include <ostream>

#include "Interagir.h"
#include "Types.h"

namespace PokemonGame {

    /**
     * @brief Classe qui représente un Pokémon.
     */
    class Pokemon : public Interagir{
    private:
        const std::string name_;
        const int maxHp_;
        int hp_;
        const std::vector<Type> types_;
        const std::string attackName_;
        const int attackPower_;

    public:
        /**
         * @brief Constructeur de la classe Pokemon.
         * @param name Nom du Pokémon.
         * @param hp Points de vie du Pokémon.
         * @param types Types du Pokémon.
         * @param attackName Nom de l'attaque du Pokémon.
         * @param attackPower Puissance de l'attaque du Pokémon.
         */
        Pokemon(const std::string& name, int hp, const std::vector<Type>& types, const std::string& attackName, int attackPower);
        Pokemon(const Pokemon& other);
        ~Pokemon() override = default;

        void applyDamage(int damage);
        void heal(int amount);
        void fullHeal();
        void displayInfo() const;
        [[nodiscard]] bool isFainted() const;
        [[nodiscard]] std::string interact() const override;
        friend std::ostream& operator<<(std::ostream& out, const Pokemon& pokemon);

        [[nodiscard]] const std::string& getName() const;
        [[nodiscard]] int getMaxHp() const;
        [[nodiscard]] int getHp() const;
        [[nodiscard]] const std::vector<Type>& getTypes() const;
        [[nodiscard]] const std::string& getAttackName() const;
        [[nodiscard]] int getAttackPower() const;
    };

} // PokemonGame

#endif //POKEMON_H
