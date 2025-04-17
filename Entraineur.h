//
// Created by olbnf on 16/04/2025.
//

#ifndef ENTRAINEUR_H
#define ENTRAINEUR_H

#include <memory>
#include <string>
#include <vector>

#include "Pokemon.h"

namespace PokemonGame {

    class Entraineur {
    protected:
        const std::string name_;
        std::vector<std::unique_ptr<Pokemon>> pokemonTeam_;
        static constexpr int limitPokemon = 6;

    public:
        explicit Entraineur(const std::string& name);
        virtual ~Entraineur() = default;

        void healTeam();
        void addPokemon(std::unique_ptr<Pokemon> pokemon);
        void removePokemon(int index);
        void switchPokemon(int index1, int index2);
        void displayTeam() const;
        [[nodiscard]] virtual bool canInteract() const = 0;

        [[nodiscard]] const std::string& getName() const;
        [[nodiscard]] const std::vector<std::unique_ptr<Pokemon>>& getPokemonTeam() const;
        [[nodiscard]] const Pokemon* getPokemon(int index) const;
    };

} // PokemonGame

#endif //ENTRAINEUR_H
