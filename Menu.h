//
// Created by olbnf on 17/04/2025.
//

#ifndef MENU_H
#define MENU_H

#include <memory>
#include <string>
#include <unordered_map>
#include <stack>

#include "TypeManager.h"
#include "CombatManager.h"
#include "DataLoader.h"
#include "Joueur.h"
#include "Leader.h"
#include "Maitre.h"


namespace PokemonGame {
    enum class MenuState {
        MAIN,
        POKEMON_LIST,
        HEAL,
        PLAYER_POKEMON_LIST,
        POKEMON_ACTIONS,
        POKEMON_REORDER_SELECT_TARGET,
        PLAYER_STATISTIQUES,
        LEADER_LIST,
        CHALLENGE_MASTER,
        INTERACT
    };

    class Menu {
    private:
        std::unique_ptr<Joueur> player_;
        std::vector<std::unique_ptr<Leader>> leaders_;
        std::vector<std::unique_ptr<Maitre>> maitres_;
        std::unordered_map<std::string, std::unique_ptr<Pokemon>> pokemons_;
        CombatManager combatManager_;
        int boxWidth_ = 80;

        std::stack<MenuState> stateStack_;
        int selectedPokemonIndex_;
        std::vector<Entraineur*> interactTrainer_;

        [[nodiscard]] bool loadData();
        [[nodiscard]] bool allLeaderDefeated() const;
        [[nodiscard]] int selectChoices(std::string& prompt, std::vector<std::string>& messages) const;

        void handleMainMenu();
        void handlePokemonList();
        void handleHeal();
        void handlePlayerPokemonList();
        void handlePlayerPokemonActions();
        void handlePokemonReorder();
        void handlePlayerStatistiques();
        void handleTrainerList();
        void handleChallengeMaster();
        void handleInteract();

        bool handleCombat(Entraineur* dresseur);

        void displayCombat(TurnInfo turn) const;
    public:
        Menu();
        ~Menu() = default;

        void run();
        void displayPokemon(CombatPokemonInfo info) const;
    };



} // PokemonGame

#endif //MENU_H
