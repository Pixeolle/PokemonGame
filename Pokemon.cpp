//
// Created by olbnf on 16/04/2025.
//

#include <iostream>
#include <stdexcept>

#include "Pokemon.h"

#include "Utils.h"

namespace PokemonGame {

    Pokemon::Pokemon(const std::string& name, int hp, const std::vector<Type>& types, const std::string& attackName, int attackPower):
        name_(Utils::String::trimValidateTitle(name, "nom du pokémon")),
        maxHp_(hp),
        hp_(hp),
        types_(types),
        attackName_(Utils::String::trimValidateTitle(attackName, "nom de l'attaque")),
        attackPower_(attackPower)
    {
        if (hp < 0) {
            throw std::invalid_argument("Les HP doivent être positifs.");
        }

        if (types.empty() || types.size() > 2) {
            throw std::invalid_argument("Un pokémon ne peut avoir que 1 ou 2 types.");
        }
    }

    Pokemon::Pokemon(const Pokemon& other) :
        name_(other.name_),
        maxHp_(other.maxHp_),
        hp_(other.hp_),
        types_(other.types_),
        attackName_(other.attackName_),
        attackPower_(other.attackPower_)
    {}

    void Pokemon::applyDamage(int damage) {
        hp_ -= std::min(hp_, damage);
    }

    void Pokemon::heal(int amount) {
        hp_ += std::min(maxHp_ - hp_, amount);
    }

    void Pokemon::fullHeal() {
        hp_ = maxHp_;
    }

    void Pokemon::displayInfo() const {
        std::cout << name_ << " (" << types_ << ") : " << hp_ << "/" << maxHp_ << "\n";
        std::cout << "   ↳ " << attackName_ << " : " << attackPower_ << std::endl;
    }

    [[nodiscard]] bool Pokemon::isFainted() const {
        return hp_ <= 0;
    }

    void Pokemon::interact() const {
        std::string sound = name_.substr(0, std::min(name_.length(), static_cast<std::string::size_type>(4)));
        sound += sound;

        std::cout << name_ << " : \"" << sound << "...\"";
    }

    std::ostream& operator<<(std::ostream& out, const Pokemon& pokemon) {
        out << pokemon.name_ << " (" << pokemon.types_ << ")";
        return out;
    }

    const std::string& Pokemon::getName() const {
        return name_;
    }

    int Pokemon::getMaxHp() const {
        return maxHp_;
    }

    int Pokemon::getHp() const {
        return hp_;
    }

    const std::vector<Type>& Pokemon::getTypes() const {
        return types_;
    }

    const std::string& Pokemon::getAttackName() const {
        return attackName_;
    }

    int Pokemon::getAttackPower() const {
        return attackPower_;
    }

} // PokemonGame