//
// Created by olbnf on 16/04/2025.
//

#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
#include <ostream>

namespace PokemonGame {

    /**
     * @enum Type
     * @brief Représente les différents types de Pokémon.
     */
    enum class Type {
        FEU,
        EAU,
        PLANTE,
        ELECTRIK,
        GLACE,
        COMBAT,
        POISON,
        SOL,
        VOL,
        PSY,
        INSECTE,
        ROCHE,
        SPECTRE,
        DRAGON,
        TENEBRES,
        ACIER,
        FEE,
        NORMAL
    };

    [[nodiscard]] std::string typeToString(Type type);
    [[nodiscard]] Type stringToType(const std::string& typeName);
    [[nodiscard]] std::string typesToString(const std::vector<Type>& types);
    std::ostream& operator<<(std::ostream& out, Type type);
    std::ostream& operator<<(std::ostream& out, const std::vector<Type>& types);

}

#endif //TYPES_H
