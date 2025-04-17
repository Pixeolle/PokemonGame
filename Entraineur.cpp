//
// Created by olbnf on 16/04/2025.
//

#include <iostream>

#include "Entraineur.h"
#include "Utils.h"

namespace PokemonGame {

    Entraineur::Entraineur(const std::string& name) :
        name_(Utils::String::trimValidateTitle(name, "nom du dresseur")),
        pokemonTeam_({}) {}

    void Entraineur::healTeam() {
        for (auto& pokemon : pokemonTeam_) {
            pokemon->fullHeal();
        }
    }

    void Entraineur::addPokemon(std::unique_ptr<Pokemon> pokemon) {
        if (pokemonTeam_.size() >= limitPokemon) {
            throw std::invalid_argument("Impossible de dépasser la limite de pokémon");
        }
        pokemonTeam_.push_back(pokemon);
    }

    void Entraineur::removePokemon(int index) {
        if (index >= pokemonTeam_.size()) {
            throw std::invalid_argument("Index hors limite");
        }
        pokemonTeam_.erase(pokemonTeam_.begin() + index);
    }

    void Entraineur::switchPokemon(int index1, int index2) {
        if (index1 >= pokemonTeam_.size() || index2 >= pokemonTeam_.size()) {
            throw std::invalid_argument("Index hors limite");
        }
        pokemonTeam_[index1].swap(pokemonTeam_[index2]);
    }

    void Entraineur::displayTeam() const {
        std::cout << "Équipe de " << name_ << " : \n";
        for (int i = 0; i < pokemonTeam_.size(); i++) {
            std::cout << pokemonTeam_[i];

            if (i < pokemonTeam_.size() - 1) {
                std::cout << "\n";
            }
        }
        std::cout << std::endl;
    }

    const std::string& Entraineur::getName() const {
        return name_;
    }

    const std::vector<std::unique_ptr<Pokemon>>& Entraineur::getPokemonTeam() const {
        return pokemonTeam_;
    }

    const Pokemon* Entraineur::getPokemon(int index) const {
        if (index >= pokemonTeam_.size()) {
            throw std::invalid_argument("Index hors limite");
        }
        return pokemonTeam_[index].get();
    }

} // PokemonGame