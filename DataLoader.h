//
// Created by olbnf on 17/04/2025.
//

#ifndef DATALOADER_H
#define DATALOADER_H

#include <string>

namespace PokemonGame {

    class DataLoader {
    public:
        DataLoader(std::string& pokemonFilePath, std::string& joueurFilePath, std::string& leaderFilePath, std::string& maitreFilePath);
        ~DataLoader() = default;
    };

} // PokemonGame

#endif //DATALOADER_H
