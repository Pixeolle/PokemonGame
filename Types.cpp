

#include "Types.h"

#include "Utils.h"

namespace PokemonGame {

    /**
     * @brief Convertit un type Pokémon en sa représentation textuelle.
     * @param type Le type Pokémon à convertir.
     * @return std::string La chaîne de caractères représentant le type.
     */
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


    /**
     * @brief Convertit une chaîne de caractères en un type Pokémon.
     * @param typeName La chaîne de caractères représentant le type.
     * @return Type Le type Pokémon correspondant.
     * @throws std::invalid_argument Si le type est inconnu.
     */
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

    /**
     * @brief Convertit une liste de types Pokémon en une chaîne de caractères.
     * @param types Le vecteur contenant les types Pokémon.
     * @return std::string La chaîne de caractères représentant les types, séparés par des espaces.
     */
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

    /**
     * @brief Surcharge de l'opérateur << pour afficher un type Pokémon.
     * @param out Le flux de sortie.
     * @param type Le type Pokémon à afficher.
     * @return std::ostream& Le flux de sortie modifié.
     */
    std::ostream& operator<<(std::ostream& out, Type type) {
        out << typeToString(type);
        return out;
    }

    /**
     * @brief Surcharge de l'opérateur << pour afficher une liste de types Pokémon.
     * @param out Le flux de sortie.
     * @param types Le vecteur contenant les types Pokémon à afficher.
     * @return std::ostream& Le flux de sortie modifié.
     */
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
