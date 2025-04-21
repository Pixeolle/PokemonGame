//
// Created by olbnf on 17/04/2025.
//

#include "Types.h"

#include "Utils.h"

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
            case Type::NORMAL: return "Normal";
        }

        return "ErreurType";
    }

    Type stringToType(const std::string& typeName) {
        std::string normaliseTypeName = Utils::String::toTitle(Utils::String::trim(typeName));

        if (normaliseTypeName == "Feu") {
            return Type::FEU;
        } if (normaliseTypeName == "Eau") {
            return Type::EAU;
        } if (normaliseTypeName == "Plante") {
            return Type::PLANTE;
        } if (normaliseTypeName == "Électrik" || normaliseTypeName == "Electrik") { // Gérer les variations possibles
            return Type::ELECTRIK;
        } if (normaliseTypeName == "Glace") {
            return Type::GLACE;
        } if (normaliseTypeName == "Combat") {
            return Type::COMBAT;
        } if (normaliseTypeName == "Poison") {
            return Type::POISON;
        } if (normaliseTypeName == "Sol") {
            return Type::SOL;
        } if (normaliseTypeName == "Vol") {
            return Type::VOL;
        } if (normaliseTypeName == "Psy") {
            return Type::PSY;
        } if (normaliseTypeName == "Insecte") {
            return Type::INSECTE;
        } if (normaliseTypeName == "Roche") {
            return Type::ROCHE;
        } if (normaliseTypeName == "Spectre") {
            return Type::SPECTRE;
        } if (normaliseTypeName == "Dragon") {
            return Type::DRAGON;
        } if (normaliseTypeName == "Ténèbres" || normaliseTypeName == "Tenebres") { // Gérer les variations possibles
            return Type::TENEBRES;
        } if (normaliseTypeName == "Acier") {
            return Type::ACIER;
        } if (normaliseTypeName == "Fée" || normaliseTypeName == "Fee") { // Gérer les variations possibles
            return Type::FEE;
        } if (normaliseTypeName == "Normal") {
            return Type::NORMAL;
        }

        throw std::invalid_argument("Type inconnu : '" + normaliseTypeName + "' (original: '" + typeName + "')");
    }

    std::string typesToString(const std::vector<Type> &types) {
        std::string result;
        for (int i = 0; i < types.size(); i++) {
             result += typeToString(types[i]);
            if (i < types.size() - 1) {
                result += " ";
            }
        }
        return result;
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
