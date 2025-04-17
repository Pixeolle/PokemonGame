//
// Created by olbnf on 16/04/2025.
//

#include <iostream>

#include "Maitre.h"

namespace PokemonGame {

    Maitre::Maitre(std::string& name) : Entraineur(name) {}

    void Maitre::setDefeated() {
        isDefeated_ = true;
    }

    void Maitre::interact() const {
        std::cout << "Tu m'as bien battu, je vais retourner m'entrainer et revenir plus fort !" << std::endl;
    }

    bool Maitre::canInteract() const {
        return isDefeated_;
    }

    const float Maitre::getDamageBonus() const {
        return damageBonus_;
    }

} // PokemonGame