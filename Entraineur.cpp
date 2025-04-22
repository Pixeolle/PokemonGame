
#include <iostream>

#include "Entraineur.h"
#include "Utils.h"

namespace PokemonGame {

    /**
     * Constructeur de la classe Entraineur
     * @param name : nom du dresseur
     */
    Entraineur::Entraineur(const std::string& name) :
        name_(Utils::String::trimValidateTitle(name, "nom du dresseur"))
        {}

    void Entraineur::healTeam() {
        for (auto& pokemon : pokemonTeam_) {
            pokemon->fullHeal();
        }
    }

    void Entraineur::addPokemon(Pokemon& pokemon) {
        if (pokemonTeam_.size() >= limitPokemon) {
            throw std::invalid_argument("Impossible de dépasser la limite de pokémon");
        }
        pokemonTeam_.emplace_back(std::make_unique<Pokemon>(pokemon)); //Place le pokemon dans l'équipe
    }

    /**
     * @brief Supprime un Pokémon de l'équipe
     * param index : index du Pokémon à supprimer
     * @throws std::invalid_argument si l'index est hors limite de l'équipe
     */
    void Entraineur::removePokemon(int index) {
        if (index >= pokemonTeam_.size()) {
            throw std::invalid_argument("Index hors limite");
        }
        pokemonTeam_.erase(pokemonTeam_.begin() + index);
    }

    /**
     * @brief Échange la position de deux Pokémon dans l'équipe
     * @param index1 : index du premier Pokémon
     * @param index2 : index du deuxième Pokémon
     * @throws std::invalid_argument si l'un des index est hors limite de l'équipe
     */
    void Entraineur::switchPokemon(int index1, int index2) {
        if (index1 >= pokemonTeam_.size() || index2 >= pokemonTeam_.size()) {
            throw std::invalid_argument("Index hors limite");
        }
        pokemonTeam_[index1].swap(pokemonTeam_[index2]);
    }

    /**
     * @brief Affiche l'équipe du dresseur
     * @param index : index du Pokémon à afficher
     * @throws std::invalid_argument si l'index est hors limite de l'équipe
     */
    void Entraineur::displayTeam() const {
        std::cout << "Équipe de " << name_ << " : \n";
        for (int i = 0; i < pokemonTeam_.size(); i++) {
            std::cout << "   ↳ " << *pokemonTeam_[i];

            if (i < pokemonTeam_.size() - 1) {
                std::cout << "\n";
            }
        }
        std::cout << std::endl;
    }


    const std::string& Entraineur::getName() const {
        return name_;
    }

    /**
     * Récupère l'équipe de Pokémon du dresseur.
     * @return Une référence constante vers le vecteur contenant les Pokémon de l'équipe.
     */
    const std::vector<std::unique_ptr<Pokemon>>& Entraineur::getPokemonTeam() const {
        return pokemonTeam_;
    }

    /**
     * Récupère un Pokémon spécifique de l'équipe.
     * @param index Index du Pokémon à récupérer.
     * @return Un pointeur vers le Pokémon correspondant.
     * @throws std::invalid_argument Si l'index est hors des limites de l'équipe.
     */
    Pokemon* Entraineur::getPokemon(int index) const {
        if (index >= pokemonTeam_.size()) {
            throw std::invalid_argument("Index hors limite");
        }
        return pokemonTeam_[index].get();
    }

} // PokemonGame