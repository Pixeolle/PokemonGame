//
// Created by olbnf on 16/04/2025.
//

#include <iostream>

#include "Leader.h"
#include "Utils.h"

namespace PokemonGame {

    /**
     * Constructeur de la classe Leader
     * @param name : nom de l'entraîneur
     * @param badge : nom du badge
     * @param gymnase : nom du gymnase
     */
    Leader::Leader(const std::string& name, const std::string& badge, const std::string& gymnase) :
        Entraineur(name),
        badge_(Utils::String::trimValidateTitle(badge, "badge")),
        gymnase_(Utils::String::trimValidateTitle(gymnase, "gymnase")) {}

    void Leader::defeated() {
        isDefeated_ = true;
    }

    /**
     * Méthode qui permet d'interagir avec le leader
     * @return un message de félicitations
     */
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

    /**
     * @brief Récupère le badge associé au leader.
     * @return Une référence constante au nom du badge.
     */
    const std::string& Leader::getBadge() const {
        return badge_;
    }

    const std::string& Leader::getGymnase() const {
        return gymnase_;
    }

} // PokemonGame