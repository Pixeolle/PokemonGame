//
// Created by olbnf on 17/04/2025.
//

#include "Utils.h"

#include <stdexcept>

namespace PokemonGame::Utils {

    std::string String::toTitle(std::string str) {
        for (int i = 0; i < str.length(); i++) {
            if (i == 0 || str[i - 1] == ' ') {
                str[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(str[i])));
            }
            else {
                str[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(str[i])));
            }
        }

        return str;
    }

    std::string String::trim(std::string str) {
        auto start = str.begin();
        while (start != str.end() && std::isspace(*start)) {
            ++start;
        }

        auto end = str.end();
        do {
            --end;
        } while (std::distance(start, end) > 0 && std::isspace(*end));

        return std::string(start, end + 1);
    }

    std::string String::trimValidate(const std::string& input, const std::string& fieldName) {
        std::string trimmed = trim(input);
        if (trimmed.empty()) {
            throw std::invalid_argument("Le " + fieldName + " ne peut pas être vide ou uniquement des espaces.");
        }

        return trimmed;
    }

    std::string String::trimValidateTitle(const std::string& input, const std::string& fieldName) {
        std::string trimmed = trim(input);
        if (trimmed.empty()) {
            throw std::invalid_argument("Le " + fieldName + " ne peut pas être vide ou uniquement des espaces.");
        }

        return toTitle(trimmed);
    }
} // PokemonGame