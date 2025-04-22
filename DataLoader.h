
#ifndef DATALOADER_H
#define DATALOADER_H

#include <memory>
#include <vector>
#include <string>
#include <unordered_map>

#include "Joueur.h"
#include "Leader.h"
#include "Maitre.h"
#include "Pokemon.h"
#include "TypeManager.h"

namespace PokemonGame {

    /**
     * @brief Class to load data from CSV files.
     */
    class DataLoader {
    private:
        std::string pokemonFilePath_;
        std::string joueurFilePath_;
        std::string leaderFilePath_;
        std::string maitreFilePath_;
        std::string typeMultipliersFilePath_;

        [[nodiscard]] static std::vector<std::string> parseCsvLine(const std::string& line, char delimiter);

    public:
        DataLoader(std::string& pokemonFilePath, std::string& joueurFilePath, std::string& leaderFilePath, std::string& maitreFilePath, std::string& typeManagerFilePath);
        ~DataLoader() = default;

        [[nodiscard]] std::unordered_map<std::string, std::unique_ptr<Pokemon>> loadPokemon() const;
        [[nodiscard]] std::unique_ptr<Joueur> loadJoueur(std::unordered_map<std::string, std::unique_ptr<Pokemon>>& pokemons) const;
        [[nodiscard]] std::vector<std::unique_ptr<Leader>> loadLeaders(std::unordered_map<std::string, std::unique_ptr<Pokemon>>& pokemons) const;
        [[nodiscard]] std::vector<std::unique_ptr<Maitre>> loadMaitres(std::unordered_map<std::string, std::unique_ptr<Pokemon>>& pokemons) const;
        void loadTypeMultipliers() const;
    };

} // PokemonGame

#endif //DATALOADER_H
