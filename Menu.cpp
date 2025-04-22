//
// Created by olbnf on 17/04/2025.
//

#include <iostream>
#include <thread>
#include <iomanip>
#include <conio.h>
#include <random>

#include "Menu.h"
#include "Utils.h"

namespace PokemonGame {

        Menu::Menu()
            : combatManager_(),
              boxWidth_(std::min(80, Utils::Display::getConsoleWidth() - 4)),
              selectedPokemonIndex_(0){

            while (!stateStack_.empty()) stateStack_.pop();
            stateStack_.push(MenuState::MAIN);

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

                dataLoader.loadTypeMultipliers();

                player_ = dataLoader.loadJoueur(pokemons_);

                leaders_ = dataLoader.loadLeaders(pokemons_);

                maitres_ = dataLoader.loadMaitres(pokemons_);

                std::cout << "Chargement des données réussi !" << std::endl;
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return true;
            }
            catch (const std::exception& e) {
                Utils::Display::clearConsole();
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

        bool Menu::allLeaderDefeated() const {
            for (auto& leader : leaders_) {
                if (!leader->canInteract()) {
                    return false;
                }
            }
            return true;
        }

        void Menu::run() {

            while (!stateStack_.empty()) {
                switch (MenuState currentState = stateStack_.top()) {
                    case MenuState::MAIN:
                        handleMainMenu();
                        break;

                    case MenuState::POKEMON_LIST:
                        handlePokemonList();
                        break;

                    case MenuState::HEAL:
                        handleHeal();
                        break;

                    case MenuState::PLAYER_POKEMON_LIST:
                        handlePlayerPokemonList();
                        break;

                    case MenuState::POKEMON_ACTIONS:
                        handlePlayerPokemonActions();
                        break;

                    case MenuState::POKEMON_REORDER_SELECT_TARGET:
                        handlePokemonReorder();
                        break;

                    case MenuState::PLAYER_STATISTIQUES:
                        handlePlayerStatistiques();
                        break;

                    case MenuState::LEADER_LIST:
                        handleTrainerList();
                        break;

                    case MenuState::CHALLENGE_MASTER:
                        handleChallengeMaster();
                        break;

                    case MenuState::INTERACT:
                        handleInteract();
                        break;
                }
            }
        }

        void Menu::handleMainMenu() {
            std::string prompt = "Menu Principal";
            std::vector<std::string> choices = {"Pokédex", "Soigner mon équipe", "Gérer mes Pokémons", "Afficher mes statistiques", "Affronter un Leader", "Défier un Maitre", "Quitter"};
            int result = selectChoices(prompt , choices);
            switch (result) {
                case -1:
                case 6:
                    stateStack_.pop();
                    break;

                case 0:
                    stateStack_.push(MenuState::POKEMON_LIST);
                    break;

                case 1:
                    stateStack_.push(MenuState::HEAL);
                    break;

                case 2:
                    stateStack_.push(MenuState::PLAYER_POKEMON_LIST);
                    break;

                case 3:
                    stateStack_.push(MenuState::PLAYER_STATISTIQUES);
                    break;

                case 4:
                    stateStack_.push(MenuState::LEADER_LIST);
                    break;

                case 5:
                    stateStack_.push(MenuState::CHALLENGE_MASTER);
                    break;
            }
        }

        void Menu::handlePokemonList() {
            Utils::Display::clearConsole();
            Utils::Display::drawBoxLine("┌", "─", "┐", boxWidth_);
            Utils::Display::printInBox("Pokédex", boxWidth_);
            Utils::Display::drawBoxLine("├", "─", "┤", boxWidth_);
            for (const auto& pokemonMap : pokemons_) {
                Pokemon* pokemon = pokemonMap.second.get();
                Utils::Display::printInBox(pokemon->getName() + "(" + typesToString(pokemon->getTypes()) + ") : " + std::to_string(pokemon->getMaxHp()) + "HP", boxWidth_);
                Utils::Display::printInBox("   ↳ " + pokemon->getAttackName() + " : " + std::to_string(pokemon->getAttackPower()), boxWidth_);
                Utils::Display::printInBox(" ", boxWidth_);
            }
            Utils::Display::drawBoxLine("└", "─", "┘", boxWidth_);
            std::cout << "Appuyez sur Entrée pour continuer..." << std::endl;
            std::cin.get();

            stateStack_.pop();
        }

        void Menu::handleHeal() {
                player_->healTeam();
                Utils::Display::clearConsole();
                Utils::Display::drawBoxLine("┌", "─", "┐", boxWidth_);
                Utils::Display::printInBox("Tous tes pokémons sont de nouveau en forme", boxWidth_);
                Utils::Display::drawBoxLine("└", "─", "┘", boxWidth_);
                std::cout << "Appuyez sur Entrée pour continuer..." << std::endl;
                std::cin.get();

                stateStack_.pop();
        }

        void Menu::handlePlayerPokemonList() {
                std::string prompt = "Mes Pokémons";
                std::vector<std::string> choices;

                for (const auto& pokemon : player_->getPokemonTeam()) {
                    choices.push_back(pokemon->getName());
                }

                int result = selectChoices(prompt , choices);
                if (result == -1) {
                    stateStack_.pop();
                    return;
                }

                selectedPokemonIndex_ = result;
                stateStack_.push(MenuState::POKEMON_ACTIONS);

        }

        void Menu::handlePlayerPokemonActions() {
            const Pokemon* selectedPokemon = player_->getPokemon(selectedPokemonIndex_);
            std::string prompt = selectedPokemon->getName();
            std::vector<std::string> choices = {"Interagir", "Changer l'Ordre"};

            int result = selectChoices(prompt , choices);
            if (result == -1) {
                stateStack_.pop();
                return;
            }

            if (result == 0) {
                Utils::Display::clearConsole();
                Utils::Display::drawBoxLine("┌", "─", "┐", boxWidth_);
                Utils::Display::printInBox(selectedPokemon->getName() + " : " + selectedPokemon->interact(), boxWidth_);
                Utils::Display::drawBoxLine("└", "─", "┘", boxWidth_);
                std::cout << "Appuyez sur Entrée pour continuer..." << std::endl;
                std::cin.get();
                selectedPokemonIndex_ = 0;
                stateStack_.pop();
            }

            if (result == 1) {
                stateStack_.push(MenuState::POKEMON_REORDER_SELECT_TARGET);
            }
        }

        void Menu::handlePokemonReorder() {
            const Pokemon* selectedPokemon = player_->getPokemon(selectedPokemonIndex_);
            std::string prompt = "Échanger " + selectedPokemon->getName() + " avec quel Pokémon ?";
            std::vector<std::string> choices;
            const auto& pokemonTeam = player_->getPokemonTeam();

            for (int i = 0; i < player_->getPokemonTeam().size(); i++) {
                if (i != selectedPokemonIndex_) {
                    choices.push_back(pokemonTeam[i]->getName());
                }
            }

            int result = selectChoices(prompt , choices);
            if (result != -1) {
                player_->swapPokemon(selectedPokemonIndex_, result >= selectedPokemonIndex_ ? result + 1 : result);
            }

            stateStack_.pop();
            stateStack_.pop();
        }

        void Menu::handlePlayerStatistiques() {
            Utils::Display::clearConsole();
            Utils::Display::drawBoxLine("┌", "─", "┐", boxWidth_);
            Utils::Display::printInBox(player_->getName(), boxWidth_);
            Utils::Display::drawBoxLine("├", "─", "┤", boxWidth_);
            Utils::Display::printInBox("Wins : " + std::to_string(player_->getWins()) + " | Losses : " + std::to_string(player_->getLosses()) , boxWidth_);
            Utils::Display::drawBoxLine("├", "─", "┤", boxWidth_);
            Utils::Display::printInBox("Badges : " + std::to_string(player_->getBadges().size()), boxWidth_);
            for (const auto& badge : player_->getBadges()) {
                Utils::Display::printInBox(badge, boxWidth_);
            }
            Utils::Display::drawBoxLine("└", "─", "┘", boxWidth_);
            std::cout << "Appuyez sur Entrée pour continuer..." << std::endl;
            std::cin.get();

            stateStack_.pop();
        }

        void Menu::handleTrainerList() {
                std::string prompt = "Liste des Leaders";
                std::vector<std::string> choices;
                for (const auto& leader : leaders_) {
                    choices.push_back(leader->getName() + " (" + leader->getGymnase() + ")");
                }

                int result = selectChoices(prompt , choices);
                if (result == -1) {
                    stateStack_.pop();
                    return;
                }

                Leader* selectedLeader = leaders_[result].get();

                if (!selectedLeader->canInteract()) {
                    bool win = handleCombat(selectedLeader);
                    if (win) {
                        player_->addBadge(selectedLeader->getBadge());
                        interactTrainer_.push_back(selectedLeader);
                    }
                }
                else {
                    Utils::Display::clearConsole();
                    Utils::Display::drawBoxLine("┌", "─", "┐", boxWidth_);
                    Utils::Display::printInBox(selectedLeader->getName() + " : " + selectedLeader->interact(), boxWidth_);
                    Utils::Display::drawBoxLine("└", "─", "┘", boxWidth_);
                    std::cout << "Appuyez sur Entrée pour continuer..." << std::endl;
                    std::cin.get();
                }
                stateStack_.pop();
            }

        void Menu::handleChallengeMaster() {
            Utils::Display::clearConsole();
            if (maitres_.empty()) {
                Utils::Display::drawBoxLine("┌", "─", "┐", boxWidth_);
                Utils::Display::printInBox("Aucun Maitre n'est disponible", boxWidth_);
                Utils::Display::drawBoxLine("└", "─", "┘", boxWidth_);
            }

            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_int_distribution<size_t> distrib(0, maitres_.size() - 1);
            size_t randomIndex = distrib(gen);

            if (handleCombat(maitres_[randomIndex].get())) {
                interactTrainer_.push_back(maitres_[randomIndex].get());
            }
            stateStack_.pop();
        }

        void Menu::handleInteract() {
            std::string prompt = "Entraineurs ";
            std::vector<std::string> choices;
            for (const auto& trainer : interactTrainer_) {
                choices.push_back(trainer->getName());
            }

            int result = selectChoices(prompt , choices);
            if (result == -1) {
                stateStack_.pop();
                return;
            }
            Entraineur* selectedTrainer = interactTrainer_[result];


            Utils::Display::clearConsole();
            Utils::Display::drawBoxLine("┌", "─", "┐", boxWidth_);
            if (Leader* leader = dynamic_cast<Leader*>(selectedTrainer)) {
                Utils::Display::printInBox(selectedTrainer->getName() + " : " + leader->interact(), boxWidth_);
            }
            else if (Maitre* maitre = dynamic_cast<Maitre*>(selectedTrainer)) {
                Utils::Display::printInBox(selectedTrainer->getName() + " : " + maitre->interact(), boxWidth_);
            }
            Utils::Display::drawBoxLine("└", "─", "┘", boxWidth_);
            std::cout << "Appuyez sur Entrée pour continuer..." << std::endl;
            std::cin.get();
        }

        bool Menu::handleCombat(Entraineur *dresseur) {
            if (!combatManager_.startCombat(player_.get(), dresseur)) {
                Utils::Display::clearConsole();
                Utils::Display::drawBoxLine("┌", "─", "┐", boxWidth_);
                Utils::Display::printInBox("Tu n'as aucun pokémon capable de se battre. Fin du combat", boxWidth_);
                Utils::Display::drawBoxLine("└", "─", "┘", boxWidth_);
                std::cout << "Appuyez sur Entrée pour commencer..." << std::endl;
                std::cin.get();
                return false;
            }
            int i = 0;
            TurnInfo turn;

            Utils::Display::clearConsole();
            displayPokemon(combatManager_.getCombatPokemonInfo(false));
            std::cout << std::endl;
            displayPokemon(combatManager_.getCombatPokemonInfo());
            std::cout << "Appuyez sur Entrée pour commencer..." << std::endl;
            std::cin.get();

            while (combatManager_.checkCombatEnd() == 0) {
                if ((i & 1) == 0) {
                    turn = combatManager_.playerTurn();
                }
                else {
                    turn = combatManager_.opponentTurn();
                }

                displayCombat(turn);

                std::cout << "Appuyez sur Entrée pour continuer..."<< std::endl;
                std::cin.get();
                i++;

            }

            dresseur->healTeam();

            if (combatManager_.checkCombatEnd() == 1) {
                return false;
            }
            return true;
        }

        void Menu::displayCombat(TurnInfo turn) const {
            Utils::Display::clearConsole();
            displayPokemon(turn.opponentPokemon);

            std::cout << std::endl;

            displayPokemon(turn.playerPokemon);
            if (!turn.messages.empty()) {
                Utils::Display::drawBoxLine("┌", "─", "┐", boxWidth_);
                for (const auto& message : turn.messages) {
                    Utils::Display::printInBox(message, boxWidth_);
                }
                Utils::Display::drawBoxLine("└", "─", "┘", boxWidth_);
            }

        }

        void Menu::displayPokemon(CombatPokemonInfo info) const {
            constexpr int offset = 9;
            Utils::Display::drawBoxLine("┌", "─", "┐", boxWidth_ - offset);
            Utils::Display::printInBox(info.name, boxWidth_ - offset);
            Utils::Display::drawBoxLine("├", "─", "┤", boxWidth_ - offset, false);
            std::cout << "────────┐" << std::endl;

            std::string playerHpStr = std::to_string(info.currentHp);
            std::string playerMaxHpStr = std::to_string(info.maxHp);
            float hpFraction = static_cast<float>(info.currentHp) / info.maxHp;

            const int maxBarVisualWidth = std::max(0, boxWidth_ - 4 - offset);
            int filledBarWidth = static_cast<int>(std::round(hpFraction * maxBarVisualWidth));
            const int barAndPaddingLimit = std::max(0, boxWidth_ - 3 - offset);
            int emptyBarPaddingWidth = std::max(0, barAndPaddingLimit - filledBarWidth);
            std::string hp = (hpFraction > 0.25f) ? "\033[32m" : "\033[31m";
            for (int i = 0; i < filledBarWidth; i++) {
                hp += "─";
            }
            hp += "\033[0m";
            hp += std::string(emptyBarPaddingWidth, ' ');
            hp += "|";

            int hpNumPadding = std::max(0, 3 - static_cast<int>(playerHpStr.length()));
            int maxHpNumPadding = std::max(0, 3 - static_cast<int>(playerMaxHpStr.length()));
            hp += std::string(hpNumPadding, ' ') + playerHpStr + "/" + playerMaxHpStr + std::string(maxHpNumPadding, ' ');


            std::cout << "| " << hp << " |" << std::endl;
            Utils::Display::drawBoxLine("└", "─", "┘", boxWidth_ - offset, false);
            std::cout << "────────┘" << std::endl;
            }

        int Menu::selectChoices(std::string &prompt, std::vector<std::string> &messages) const {
            int index = 0;
            int input = 0;
            while (true) {
                Utils::Display::clearConsole();
                Utils::Display::displayBoxChoices(prompt + " (Entree : Valider / Supprimer : Retour)", messages, boxWidth_, index);
                input = _getch();

                switch (input) {
                    case 8: return -1;
                    case 13: return index;
                    case 224:
                        input = _getch();
                        switch (input) {
                            case 72:
                                index -= index > 0 ? 1 : 0;
                                break;
                            case 80:
                                index += index < messages.size() - 1 ? 1 : 0;
                                break;
                            case 83:
                                return -1;
                        }

                }
            }
        }


} // PokemonGame