//
// Created by olbnf on 16/04/2025.
//

#include <iostream>

#include "Leader.h"
#include "Utils.h"

namespace PokemonGame {

    Leader::Leader(const std::string& name, const std::string& badge, const std::string& gymnase) :
        Entraineur(name),
        badge_(Utils::String::trimValidateTitle(badge, "badge")),
        gymnase_(Utils::String::trimValidateTitle(gymnase, "gymnase")) {}

    void Leader::defeated() {
        isDefeated_ = true;
    }

    std::string Leader::interact() const {
        std::string message = "Bravo, continue! Grâce à ce badge et ceux des autres tu pourras défier un maitre!";
        return message;
    }

    void Leader::displayInfo() const {
        std::cout << name_ << " : " << gymnase_ << " -> " << badge_ << std::endl;
    }

    bool Leader::canInteract() const {
        return isDefeated_;
    }

    const std::string& Leader::getBadge() const {
        return badge_;
    }

    const std::string& Leader::getGymnase() const {
        return gymnase_;
    }

} // PokemonGame