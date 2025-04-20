//
// Created by olbnf on 17/04/2025.
//

#include <iostream>
#include <thread>
#include <iomanip>

#include "Menu.h"
#include "Utils.h"

namespace PokemonGame {

        Menu::Menu()
            : typeManager_(TypeManager::getInstance()),
              combatManager_(typeManager_),
              boxWidth_(std::min(80, Utils::Display::getConsoleWidth() - 4)){

            int consoleWidth = Utils::Display::getConsoleWidth();
            int boxWidth = std::min(80, consoleWidth - 4);
            std::string input;
            std::string resultInput;

            bool dataLoaded = false;
            bool out = false;

            while (!dataLoaded && !out) {
                dataLoaded = loadData();

                if (!dataLoaded) {
                    std::cout << "│ " << std::left << std::setw(boxWidth - 3) << "Voulez vous essayer à nouveau (Yes / No)?" << "│" << std::endl;
                    std::cout << "│   [Défaut: " << std::left << std::setw(boxWidth - 14) << "yes]" << "│" << std::endl;
                    std::cout << "│ Entrez le chemin (ou laissez vide pour défaut): " << std::left << std::setw(boxWidth - 49) << "" << "│" << std::endl;
                    Utils::Display::drawBoxLine("├", "─", "┤", boxWidth);
                    std::cout << "│ > ";

                    if (std::getline(std::cin, input)) {
                        if (input.empty()) {
                            resultInput = "Yes";
                            std::cout << "│ -> Nouvelle tentative." << std::left << std::setw(boxWidth - 36) << "" << "│" << std::endl;

                        } else {
                            resultInput = Utils::String::trimValidateTitle(input, "");
                            std::cout << "│ -> Saisi: " << std::left << std::setw(boxWidth-20) << resultInput << "│" << std::endl;
                            if (resultInput == "No") {
                                out = true;
                            }
                        }
                    } else {
                        throw std::invalid_argument("Erreur de lecture de l'entrée.");
                    }
                    Utils::Display::drawBoxLine("├", "─", "┤", boxWidth);
                }

            }
            if (!out) {
                run();
            }
        }

        bool Menu::loadData() {

            Utils::Display::clearConsole();

            const std::string defaultPokemonFile = R"(C:\Users\olbnf\Downloads\pokemon.csv)";
            const std::string defaultJoueurFile = R"(C:\Users\olbnf\Downloads\joueur.csv)";
            const std::string defaultLeadersFile = R"(C:\Users\olbnf\Downloads\leaders.csv)";
            const std::string defaultMaitresFile = R"(C:\Users\olbnf\Downloads\maitres.csv)";
            const std::string defaultTypesMultiplierFile = R"(C:\Users\olbnf\Downloads\typeMatrixPokemon.csv)";

            std::string pokemonFilePath = defaultPokemonFile;
            std::string typeMultipliersFilePath = defaultTypesMultiplierFile;
            std::string joueurFilePath = defaultJoueurFile;
            std::string leaderFilePath = defaultLeadersFile;
            std::string maitreFilePath = defaultMaitresFile;

            Utils::Display::drawBoxLine("┌", "─", "┐", boxWidth_);
            Utils::Display::printInBox("Configuration des Fichiers de Données", boxWidth_);
            Utils::Display::drawBoxLine("├", "─", "┤", boxWidth_);

            try {
                Utils::String::promptAndValidatePath("Chemin Fichier Pokémon:", defaultPokemonFile, pokemonFilePath, boxWidth_);
                Utils::String::promptAndValidatePath("Chemin Fichier Types:", defaultTypesMultiplierFile, typeMultipliersFilePath, boxWidth_);
                Utils::String::promptAndValidatePath("Chemin Fichier Joueur:", defaultJoueurFile, joueurFilePath, boxWidth_);
                Utils::String::promptAndValidatePath("Chemin Fichier Leaders:", defaultLeadersFile, leaderFilePath, boxWidth_);
                Utils::String::promptAndValidatePath("Chemin Fichier Maîtres:", defaultMaitresFile, maitreFilePath, boxWidth_);

                Utils::Display::printInBox("Tous les chemins sont valides. Chargement...", boxWidth_);
                Utils::Display::drawBoxLine("└", "─", "┘", boxWidth_);

                std::cout << "\nChemins finaux utilisés :" << std::endl;
                std::cout << "- Pokémon: " << pokemonFilePath << std::endl;
                std::cout << "- Types: " << typeMultipliersFilePath << std::endl;
                std::cout << "- Joueur: " << joueurFilePath << std::endl;
                std::cout << "- Leaders: " << leaderFilePath << std::endl;
                std::cout << "- Maîtres: " << maitreFilePath << std::endl;
                std::cout << "\nAppuyez sur Entrée pour continuer..." << std::endl;
                std::cin.get();

                DataLoader dataLoader(pokemonFilePath, joueurFilePath, leaderFilePath, maitreFilePath, typeMultipliersFilePath);

                pokemons_ = dataLoader.loadPokemon();

                dataLoader.loadTypeMultipliers(typeManager_);

                player_ = dataLoader.loadJoueur(pokemons_);

                leaders_ = dataLoader.loadLeaders(pokemons_);

                maitres_ = dataLoader.loadMaitres(pokemons_);

                std::cout << "Chargement des données réussi !" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(2));
                return true;
            }
            catch (const std::exception& e) {
                //Utils::Display::clearConsole();
                std::cerr << "\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                std::cerr << "ERREUR CRITIQUE lors du chargement des données :" << std::endl;
                std::cerr << e.what() << std::endl;
                std::cerr << "Vérifiez les chemins et le contenu des fichiers." << std::endl;
                std::cerr << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n" << std::endl;
                std::cout << "Appuyez sur Entrée pour quitter..." << std::endl;
                std::cin.get();
                return false;
            }
        }

        bool Menu::isOver() const {
            for (auto& leader : leaders_) {
                if (!leader->canInteract()) {
                    return false;
                }
            }

            for (auto& maitre : maitres_) {
                if (!maitre->canInteract()) {
                    return false;
                }
            }
            return true;
        }


        void Menu::run() {



            Utils::Display::drawBoxLine("└", "─", "┘", boxWidth_);
            std::cout << "Le jeu Commence !!" << std::endl;

            player_->displayStats();
            player_->displayTeam();

            std::cout << std::endl;

            for (auto& leader : leaders_) {
                leader->displayInfo();
                leader->displayTeam();
            }

            std::cout << std::endl;

            for (auto& maitre : maitres_) {
                maitre->displayTeam();
            }

        }

} // PokemonGame