

#include <sstream>
#include <fstream>
#include <iostream>
#include <vector>
#include <memory>

#include "DataLoader.h"
#include "Utils.h"
#include "Types.h"

namespace PokemonGame {

    /**
     * Constructeur de la classe DataLoader.
     * Initialise les chemins des fichiers nécessaires pour charger les données.
     * @param pokemonFilePath Chemin du fichier contenant les données des Pokémon.
     * @param joueurFilePath Chemin du fichier contenant les données du joueur.
     * @param leaderFilePath Chemin du fichier contenant les données des leaders.
     * @param maitreFilePath Chemin du fichier contenant les données des maîtres.
     * @param typeManagerFilePath Chemin du fichier contenant la table des multiplicateurs de types.
     */
    DataLoader::DataLoader(std::string& pokemonFilePath, std::string& joueurFilePath, std::string& leaderFilePath, std::string& maitreFilePath, std::string& typeManagerFilePath) :
        pokemonFilePath_(Utils::String::trimValidate(pokemonFilePath, "chemin du fichier pokémon")),
        joueurFilePath_(Utils::String::trimValidate(joueurFilePath, "chemin du fichier joueur")),
        leaderFilePath_(Utils::String::trimValidate(leaderFilePath, "chemin du fichier leader")),
        maitreFilePath_(Utils::String::trimValidate(maitreFilePath, "chemin du fichier maitre")),
        typeMultipliersFilePath_(Utils::String::trimValidate(typeManagerFilePath, "chemin du fichier de la table des types"))
    {}

    /**
     * Analyse une ligne CSV en fonction d'un délimiteur donné.
     * @param line Ligne CSV à analyser.
     * @param delimiter Caractère délimitant les champs (par défaut ',').
     * @return Un vecteur contenant les champs extraits de la ligne.
     */
    std::vector<std::string> DataLoader::parseCsvLine(const std::string& line, char delimiter = ',') {
        std::vector<std::string> fields;
        std::stringstream ss(line);
        std::string field;

        while (std::getline(ss, field, delimiter)) {
            field = Utils::String::trim(field);
            fields.push_back(field);
        }

        return fields;
    }

    /**
     * Charge les données des Pokémon à partir du fichier CSV.
     * @return Une map associant le nom des Pokémon à leurs objets correspondants.
     * @throws std::invalid_argument Si le fichier ne peut pas être ouvert.
     * @throws std::runtime_error Si des colonnes requises sont manquantes dans le fichier.
     */
    std::unordered_map<std::string, std::unique_ptr<Pokemon>> DataLoader::loadPokemon() const {
        std::ifstream file(pokemonFilePath_);
        if (!file.is_open()) {
            throw std::invalid_argument("Impossible d'ouvrir  le fichier " + pokemonFilePath_);
        }

        std::unordered_map<std::string, std::unique_ptr<Pokemon>> pokemons;

        bool firstLine = true;
        std::unordered_map<std::string, int> headerMap;
        std::string line;

        while (std::getline(file, line)) {
            std::vector<std::string> fields = parseCsvLine(line);
            if (firstLine) {
                for (int i = 0; i < fields.size(); i++) {
                    headerMap[fields[i]] = i;
                }

                if (headerMap.find("Nom") == headerMap.end() ||
                    headerMap.find("Points de Vie") == headerMap.end() ||
                    headerMap.find("Type 1") == headerMap.end() ||
                    headerMap.find("Attaque") == headerMap.end() ||
                    headerMap.find("Dégâts d'Attaque") == headerMap.end()) {

                    throw std::runtime_error("Une ou plusieurs colonnes CSV requises sont manquantes dans l'en-tête de " + pokemonFilePath_ + ".");
                }

                firstLine = false;
                continue;
            }

            if (fields.size() < headerMap.size()) {
                fields.resize(headerMap.size(), "");
            }

            try {
                std::string name = fields[headerMap.at("Nom")];
                int hp = std::stoi(fields[headerMap.at("Points de Vie")]);
                std::vector<Type> types;

                if (!fields[headerMap.at("Type 1")].empty()) {
                    types.push_back(stringToType(fields[headerMap.at("Type 1")]));
                }
                if (headerMap.find("Type 2") != headerMap.end() && !fields[headerMap.at("Type 2")].empty()) {
                    types.push_back(stringToType(fields[headerMap.at("Type 2")]));
                }

                if (types.empty()) {
                    throw std::invalid_argument("Aucun type valide trouvé pour " + name);
                }

                std::string attackName = fields[headerMap.at("Attaque")];
                int attackPower = std::stoi(fields[headerMap.at("Dégâts d'Attaque")]);

                std::unique_ptr<Pokemon> pokemon = std::make_unique<Pokemon>(name, hp, types, attackName, attackPower);
                pokemons.emplace(name, std::move(pokemon));

            } catch (const std::invalid_argument& e) {
                std::cerr << "Erreur de conversion (nombre invalide?) pour la ligne Pokémon: [" << line << "] (" << e.what() << ")" << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Erreur de conversion (nombre trop grand?) pour la ligne Pokémon: [" << line << "] (" << e.what() << ")" << std::endl;
            } catch (const std::runtime_error& e) {
                std::cerr << "Erreur lors du traitement de la ligne Pokémon: [" << line << "] (" << e.what() << ")" << std::endl;
            }
        }
        file.close();
        return pokemons;
    }

    /***
     * Charge les données du joueur à partir du fichier CSV.
     * @param pokemons Map associant le nom des Pokémon à leurs objets correspondants.
     * @return Un pointeur unique vers l'objet Joueur chargé.
     * @throws std::invalid_argument Si le fichier ne peut pas être ouvert.
     * @throws std::runtime_error Si des colonnes requises sont manquantes dans le fichier.
     */
    std::unique_ptr<Joueur> DataLoader::loadJoueur(std::unordered_map<std::string, std::unique_ptr<Pokemon>>& pokemons) const {
        std::ifstream file(joueurFilePath_);
        if (!file.is_open()) {
            throw std::invalid_argument("Impossible d'ouvrir  le fichier " + joueurFilePath_);
        }

        std::unique_ptr<Joueur> player;

        bool firstLine = true;
        std::unordered_map<std::string, int> headerMap;
        std::string line;

        while (std::getline(file, line)) {
            std::vector<std::string> fields = parseCsvLine(line);
            if (firstLine) {
                for (int i = 0; i < fields.size(); i++) {
                    headerMap[fields[i]] = i;
                }

                if (headerMap.find("Nom") == headerMap.end() ||
                    headerMap.find("Pokemon1") == headerMap.end() ||
                    headerMap.find("Pokemon2") == headerMap.end() ||
                    headerMap.find("Pokemon3") == headerMap.end() ||
                    headerMap.find("Pokemon4") == headerMap.end() ||
                    headerMap.find("Pokemon5") == headerMap.end() ||
                    headerMap.find("Pokemon6") == headerMap.end()) {

                    throw std::runtime_error("Une ou plusieurs colonnes CSV requises sont manquantes dans l'en-tête de " + joueurFilePath_ + ".");
                }

                firstLine = false;
                continue;
            }

            if (fields.size() < headerMap.size()) {
                fields.resize(headerMap.size(), "");
            }

            try {
                std::string name = fields[headerMap.at("Nom")];
                player = std::make_unique<Joueur>(name);
                for (int i = 1; i <= 6; i++) {
                    std::string pokemonName = fields[headerMap.at("Pokemon" + std::to_string(i))];
                    if (!pokemonName.empty()) {
                        player->addPokemon(*pokemons.at(pokemonName));
                    }
                }

            } catch (const std::invalid_argument& e) {
                std::cerr << "Erreur de conversion (nombre invalide?) pour la ligne Pokémon: [" << line << "] (" << e.what() << ")" << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Erreur d'insertion, pokemon inconnu: [" << line << "] (" << e.what() << ")" << std::endl;
            } catch (const std::runtime_error& e) {
                std::cerr << "Erreur lors du traitement de la ligne Pokémon: [" << line << "] (" << e.what() << ")" << std::endl;
            }
        }
        file.close();
        return player;
    }

    std::vector<std::unique_ptr<Leader>> DataLoader::loadLeaders(std::unordered_map<std::string, std::unique_ptr<Pokemon>>& pokemons) const {
        std::ifstream file(leaderFilePath_);
        if (!file.is_open()) {
            throw std::invalid_argument("Impossible d'ouvrir  le fichier " + leaderFilePath_);
        }

        std::vector<std::unique_ptr<Leader>> leaders;

        bool firstLine = true;
        std::unordered_map<std::string, int> headerMap;
        std::string line;

        while (std::getline(file, line)) {
            std::vector<std::string> fields = parseCsvLine(line);
            if (firstLine) {
                for (int i = 0; i < fields.size(); i++) {
                    headerMap[fields[i]] = i;
                }

                if (headerMap.find("Nom") == headerMap.end() ||
                    headerMap.find("Gymnase") == headerMap.end() ||
                    headerMap.find("Medaille") == headerMap.end() ||
                    headerMap.find("Pokemon1") == headerMap.end() ||
                    headerMap.find("Pokemon2") == headerMap.end() ||
                    headerMap.find("Pokemon3") == headerMap.end() ||
                    headerMap.find("Pokemon4") == headerMap.end() ||
                    headerMap.find("Pokemon5") == headerMap.end() ||
                    headerMap.find("Pokemon6") == headerMap.end()) {

                    throw std::runtime_error("Une ou plusieurs colonnes CSV requises sont manquantes dans l'en-tête de " + joueurFilePath_ + ".");
                }

                firstLine = false;
                continue;
            }

            if (fields.size() < headerMap.size()) {
                fields.resize(headerMap.size(), "");
            }

            try {
                std::string name = fields[headerMap.at("Nom")];
                std::string gymnase = fields[headerMap.at("Gymnase")];
                std::string badge = fields[headerMap.at("Medaille")];
                std::unique_ptr<Leader> leader = std::make_unique<Leader>(name, badge, gymnase);
                for (int i = 1; i <= 6; i++) {
                    std::string pokemonName = fields[headerMap.at("Pokemon" + std::to_string(i))];
                    if (!pokemonName.empty()) {
                        leader->addPokemon(*pokemons.at(pokemonName));
                    }
                }
                leaders.push_back(std::move(leader));

            } catch (const std::invalid_argument& e) {
                std::cerr << "Erreur de conversion (nombre invalide?) pour la ligne Pokémon: [" << line << "] (" << e.what() << ")" << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Erreur d'insertion, pokemon inconnu: [" << line << "] (" << e.what() << ")" << std::endl;
            } catch (const std::runtime_error& e) {
                std::cerr << "Erreur lors du traitement de la ligne Pokémon: [" << line << "] (" << e.what() << ")" << std::endl;
            }
        }
        file.close();
        return leaders;
    }

    std::vector<std::unique_ptr<Maitre>> DataLoader::loadMaitres(std::unordered_map<std::string, std::unique_ptr<Pokemon>>& pokemons) const {
        std::ifstream file(maitreFilePath_);
        if (!file.is_open()) {
            throw std::invalid_argument("Impossible d'ouvrir  le fichier " + maitreFilePath_);
        }

        std::vector<std::unique_ptr<Maitre>> maitres;

        bool firstLine = true;
        std::unordered_map<std::string, int> headerMap;
        std::string line;

        while (std::getline(file, line)) {
            std::vector<std::string> fields = parseCsvLine(line);
            if (firstLine) {
                for (int i = 0; i < fields.size(); i++) {
                    headerMap[fields[i]] = i;
                }

                if (headerMap.find("Nom") == headerMap.end() ||
                    headerMap.find("Pokemon1") == headerMap.end() ||
                    headerMap.find("Pokemon2") == headerMap.end() ||
                    headerMap.find("Pokemon3") == headerMap.end() ||
                    headerMap.find("Pokemon4") == headerMap.end() ||
                    headerMap.find("Pokemon5") == headerMap.end() ||
                    headerMap.find("Pokemon6") == headerMap.end()) {

                    throw std::runtime_error("Une ou plusieurs colonnes CSV requises sont manquantes dans l'en-tête de " + joueurFilePath_ + ".");
                }

                firstLine = false;
                continue;
            }

            if (fields.size() < headerMap.size()) {
                fields.resize(headerMap.size(), "");
            }

            try {
                std::string name = fields[headerMap.at("Nom")];
                auto maitre = std::make_unique<Maitre>(name);
                for (int i = 1; i <= 6; i++) {
                    std::string pokemonName = fields[headerMap.at("Pokemon" + std::to_string(i))];
                    if (!pokemonName.empty()) {
                        maitre->addPokemon(*pokemons.at(pokemonName));
                    }
                }

                maitres.push_back(std::move(maitre));

            } catch (const std::invalid_argument& e) {
                std::cerr << "Erreur de conversion (nombre invalide?) pour la ligne Pokémon: [" << line << "] (" << e.what() << ")" << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Erreur d'insertion, pokemon inconnu: [" << line << "] (" << e.what() << ")" << std::endl;
            } catch (const std::runtime_error& e) {
                std::cerr << "Erreur lors du traitement de la ligne Pokémon: [" << line << "] (" << e.what() << ")" << std::endl;
            }
        }
        file.close();
        return maitres;
    }

    void DataLoader::loadTypeMultipliers() const {
        std::ifstream file(typeMultipliersFilePath_);
        if (!file.is_open()) {
            throw std::invalid_argument("Impossible d'ouvrir  le fichier " + typeMultipliersFilePath_);
        }

        std::unordered_map<Type, std::unordered_map<Type, float>> multipliers;

        bool firstLine = true;
        std::unordered_map<int, Type> defenseTypeMap;
        std::string line;

        while (std::getline(file, line)) {
            std::vector<std::string> fields = parseCsvLine(line);
            if (firstLine) {
                for (int i = 1; i < fields.size(); i++) {
                    defenseTypeMap[i] = stringToType(fields[i]);
                }

                firstLine = false;
                continue;
            }

            if (fields.size() < defenseTypeMap.size()) {
                fields.resize(defenseTypeMap.size(), "");
            }

            try {
                Type attackType = stringToType(fields[0]);
                for (int i = 1; i < defenseTypeMap.size(); i++) {
                    if (!fields[i].empty()) {
                        multipliers[attackType][defenseTypeMap[i]] = std::stof(fields[i]);
                    }
                }

            } catch (const std::invalid_argument& e) {
                std::cerr << "Erreur de conversion (nombre invalide?) pour la ligne Pokémon: [" << line << "] (" << e.what() << ")" << std::endl;
            } catch (const std::out_of_range& e) {
                std::cerr << "Erreur d'insertion, pokemon inconnu: [" << line << "] (" << e.what() << ")" << std::endl;
            } catch (const std::runtime_error& e) {
                std::cerr << "Erreur lors du traitement de la ligne Pokémon: [" << line << "] (" << e.what() << ")" << std::endl;
            }
        }
        file.close();
        TypeManager& typeManager = TypeManager::getInstance();
        typeManager.loadMultipliers(multipliers);
    }

} // PokemonGame