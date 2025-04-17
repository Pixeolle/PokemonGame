//
// Created by olbnf on 17/04/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>

namespace PokemonGame::Utils::String {

    [[nodiscard]] std::string toTitle(std::string str);

    [[nodiscard]] std::string trim(std::string str);

    [[nodiscard]] std::string trimValidateTitle(const std::string& input, const std::string& fieldName);

} // PokemonGame

#endif //UTILS_H
