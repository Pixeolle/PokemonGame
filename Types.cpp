//
// Created by olbnf on 17/04/2025.
//

#include "Types.h"

namespace PokemonGame {

    std::string typeToString(Type type) {
        switch (type) {
            case Type::FEU:    return "Feu";
            case Type::EAU:    return "Eau";
            case Type::PLANTE: return "Plante";
            case Type::ELECTRIK: return "Électrik";
            case Type::GLACE: return "Glace";
            case Type::COMBAT: return "Combat";
            case Type::POISON: return "Poison";
            case Type::SOL: return "Sol";
            case Type::VOL: return "Vol";
            case Type::PSY: return "Psy";
            case Type::INSECTE: return "Insecte";
            case Type::ROCHE: return "Roche";
            case Type::SPECTRE: return "Spectre";
            case Type::DRAGON: return "Dragon";
            case Type::TENEBRES: return "Ténèbres";
            case Type::ACIER: return "Acier";
            case Type::FEE: return "Fée";
        }

        return "ErreurType";
    }

    std::ostream& operator<<(std::ostream& out, Type type) {
        out << typeToString(type);
        return out;
    }

    std::ostream& operator<<(std::ostream& out, const std::vector<Type>& types) {
        for (int i = 0; i < types.size(); i++) {
            out << types[i];
            if (i < types.size() - 1) {
                out << " ";
            }
        }
        return out;
    }




}