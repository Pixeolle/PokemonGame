
#include <iostream>

#include "Joueur.h"
#include "Utils.h"

namespace PokemonGame {

    /**
     * Constructeur de la classe Joueur.
     * Initialise un joueur avec un nom donné.
     * @param name Nom du joueur.
     */
    Joueur::Joueur(const std::string& name) : Entraineur(name) {}

    /**
     * Ajoute un badge à la collection du joueur.
     * @param badgeName Nom du badge à ajouter.
     * @throws std::invalid_argument Si le nom du badge est vide.
     */
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

    /**
     * Vérifie si le joueur peut interagir.
     * @return Toujours false, car cette méthode est surchargée pour le joueur.
     */
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

    /**
     * Échange la position de deux Pokémon dans l'équipe du joueur.
     * @param index1 Index du premier Pokémon.
     * @param index2 Index du second Pokémon.
     */
    void Joueur::swapPokemon(int index1, int index2) {
        std::swap(pokemonTeam_[index1], pokemonTeam_[index2]);
    }


} // PokemonGame