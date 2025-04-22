//
// Created by olbnf on 16/04/2025.
//

#include <iostream>

#include "Maitre.h"

namespace PokemonGame {

    /**
     * classe Maitre
     * @brief Représente un maître Pokémon dans le jeu, hérite de la classe Entraineur.
     * La classe Maitre contient des fonctionnalités spécifiques à un maître Pokémon,
     * telles que la gestion de son état de défaite, l'interaction avec les joueurs,
     * et un bonus de dégâts.
     */

    /**
     * Constructeur de la classe Maitre
     * @param name : nom du Maitre
     */
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