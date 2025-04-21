//
// Created by olbnf on 16/04/2025.
//

#include <iostream>

#include "Maitre.h"

namespace PokemonGame {

    Maitre::Maitre(std::string& name) : Entraineur(name) {}

    void Maitre::defeated() {
        isDefeated_ = true;
    }

    std::string Maitre::interact() const {
        std::string message = "Tu m'as bien battu, je vais retourner m'entrainer et revenir plus fort !";
        return message;
    }

    bool Maitre::canInteract() const {
        return isDefeated_;
    }

    float Maitre::getDamageBonus() const {
        return damageBonus_;
    }

} // PokemonGame