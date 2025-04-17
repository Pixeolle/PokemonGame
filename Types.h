//
// Created by olbnf on 16/04/2025.
//

#ifndef TYPES_H
#define TYPES_H

#include <string>
#include <vector>
#include <ostream>

namespace PokemonGame {

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
        FEE
    };

    [[nodiscard]] std::string typeToString(Type type);
    std::ostream& operator<<(std::ostream& out, Type type);
    std::ostream& operator<<(std::ostream& out, const std::vector<Type>& types);

}

#endif //TYPES_H
