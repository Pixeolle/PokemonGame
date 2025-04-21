//
// Created by olbnf on 16/04/2025.
//

#include <iostream>

#include "Joueur.h"
#include "Utils.h"

namespace PokemonGame {

    Joueur::Joueur(const std::string& name) : Entraineur(name) {}

    void Joueur::addBadge(const std::string& badgeName) {
        if (badgeName.empty()) {
            throw std::invalid_argument("Le nom du badge ne peut pas être vide.");
        }
        badges_.insert(Utils::String::toTitle(badgeName));
    }

    void Joueur::addWin() {
        wins_++;
    }

    void Joueur::defeated() {
        losses_++;
    }

    void Joueur::displayStats() const {
        std::cout << name_ << " : " << wins_ << "/" << losses_ << std::endl;
    }

    bool Joueur::canInteract() const {
        return false;
    }

    const std::unordered_set<std::string>& Joueur::getBadges() const {
        return badges_;
    }

    int Joueur::getWins() const {
        return wins_;
    }

    int Joueur::getLosses() const {
        return losses_;
    }

    void Joueur::swapPokemon(int index1, int index2) {
        std::swap(pokemonTeam_[index1], pokemonTeam_[index2]);
    }


} // PokemonGame