
#include <iostream>

#include "CombatManager.h"

#include "Utils.h"

namespace PokemonGame {


    /**
     * Constructeur de la classe CombatManager.
     * Initialise le gestionnaire de types et les indices de Pokémon du joueur et de l'adversaire à 0.
     */
    CombatManager::CombatManager() : typeManager_(TypeManager::getInstance()), playerPokemonIndex_(0), opponentPokemonIndex_(0) {}

    /**
     * Vérifie si le combat est terminé.
     * @return -1 si le joueur a perdu, 1 si l'adversaire a perdu, 0 si le combat continue.
     */
    int CombatManager::checkCombatEnd() const {

        if (trainerKO(player_)) {
            return -1;
        }

        if (trainerKO(entraineur_)) {
            return 1;
        }

        return 0;
    }

    /**
     * Trouve le premier Pokémon disponible dans l'équipe d'un entraîneur.
     * @param trainer L'entraîneur dont on veut vérifier l'équipe de Pokémon.
     * @return L'index du premier Pokémon disponible, ou -1 si aucun n'est disponible.
     */
    int CombatManager::findFirstPokemonAvailable(const Entraineur* trainer) {
        const auto& pokemonTeam = trainer->getPokemonTeam(); //évite de copier le vecteur retourné, on utilise une référence.
        for (int i = 0; i < pokemonTeam.size(); i++) {
            if (!pokemonTeam[i]->isFainted()) {
                return i;
            }
        }
        return -1;
    }

    /**
     * Vérifie si tous les Pokémon d'un entraîneur sont KO.
     * @param trainer L'entraîneur à vérifier.
     * @return true si tous les Pokémon sont KO, false sinon.
     */
    bool CombatManager::trainerKO(Entraineur* trainer) {
        for (const auto& pokemon : trainer->getPokemonTeam()) {
            if (pokemon->getHp() != 0) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief Démarre un combat entre un joueur et un entraîneur.
     * On initialise les Pokémon du joueur et de l'adversaire avec le premier Pokémon disponible.
     * @param player Le joueur qui combat.
     * @param opponent L'entraîneur contre lequel le joueur combat.
     * @return true si le combat a pu commencer, false sinon.
     */
    bool CombatManager::startCombat(Joueur *player, Entraineur *opponent) {
        player_ = player;
        entraineur_ = opponent;
        playerPokemonIndex_ = findFirstPokemonAvailable(player);
        opponentPokemonIndex_ = findFirstPokemonAvailable(opponent);

        if (playerPokemonIndex_ == -1 || opponentPokemonIndex_ == -1) {
            player_ = nullptr;
            entraineur_ = nullptr;
            return false;
        }
        return true;
    }

    /**
     * @brief Gère le tour du joueur pendant le combat.
     * Calcul les dégâts infligés par le Pokémon du joueur à celui de l'adversaire, et les pokémons vaincus..
     * @return Un objet TurnInfo contenant les informations sur le tour du joueur.
     */
    TurnInfo CombatManager::playerTurn() {
        TurnInfo info;
        Pokemon* playerPokemon = player_->getPokemon(playerPokemonIndex_);
        Pokemon* opponentPokemon = entraineur_->getPokemon(opponentPokemonIndex_);
        int damage = playerPokemon->getAttackPower();


        info.messages.push_back(playerPokemon->getName() + " attaque " + playerPokemon->getAttackName());
        float multiplier = typeManager_.getMultiplier(playerPokemon->getTypes(), opponentPokemon->getTypes());
        int totalDamage = static_cast<int>(damage * multiplier);
        info.messages.push_back(playerPokemon->getName() + " inflige " + std::to_string(totalDamage) + " dégâts");
        if (multiplier >= 2) {
            info.messages.emplace_back("C'est super efficace !!");
        }
        else if (multiplier <= 0.5){
            info.messages.emplace_back("Ce n'est pas très efficace...");
        }

        opponentPokemon->applyDamage(totalDamage);

        if (opponentPokemon->isFainted()) {
            info.messages.push_back(opponentPokemon->getName() + " n'est plus capable de se battre");

            if (opponentPokemonIndex_ < entraineur_->getPokemonTeam().size() - 1) {
                opponentPokemonIndex_++;
                opponentPokemon = entraineur_->getPokemon(opponentPokemonIndex_);
                info.messages.push_back(entraineur_->getName() + " envoie " + opponentPokemon->getName());
            }
            else {
                info.messages.push_back("Vous avez battu " + entraineur_->getName());
                entraineur_->defeated();
                player_->addWin();
            }
        }

        info.playerPokemon = CombatPokemonInfo(playerPokemon->getName(), playerPokemon->getHp(), playerPokemon->getMaxHp());
        info.opponentPokemon = CombatPokemonInfo(opponentPokemon->getName(), opponentPokemon->getHp(), opponentPokemon->getMaxHp());

        return info;
    }

    /**
     * @brief Gère le tour de l'adversaire pendant le combat.
     * Calcul les dégâts infligés par le Pokémon de l'adversaire à celui du joueur, et les pokémons vaincus..
     * @return Un objet TurnInfo contenant les informations sur le tour de l'adversaire.
     */
    TurnInfo CombatManager::opponentTurn() {
        TurnInfo info;
        Pokemon* playerPokemon = player_->getPokemon(playerPokemonIndex_);
        Pokemon* opponentPokemon = entraineur_->getPokemon(opponentPokemonIndex_);
        int damage = playerPokemon->getAttackPower();

        info.messages.push_back(opponentPokemon->getName() + " attaque " + opponentPokemon->getAttackName());
        float multiplier = typeManager_.getMultiplier(opponentPokemon->getTypes(), playerPokemon->getTypes());
        int totalDamage = static_cast<int>(damage * multiplier);

        info.messages.push_back(opponentPokemon->getName() + " inflige à " + std::to_string(totalDamage) + " dégâts");
        if (multiplier >= 2) {
            info.messages.emplace_back("C'est super efficace !!");
        }
        else if (multiplier <= 0.5){
            info.messages.emplace_back("Ce n'est pas très efficace...");
        }

        playerPokemon->applyDamage(totalDamage);

        if (playerPokemon->isFainted()) {
            info.messages.push_back(playerPokemon->getName() + " n'est plus capable de se battre");

            if (playerPokemonIndex_ < player_->getPokemonTeam().size() - 1) {
                playerPokemonIndex_++;
                playerPokemon = player_->getPokemon(playerPokemonIndex_);
                info.messages.push_back("Vous envoyez " + playerPokemon->getName());
            }
            else {
                info.messages.push_back("Vous avez été battu par " + entraineur_->getName());
                player_->defeated();
            }
        }

        info.playerPokemon = CombatPokemonInfo(playerPokemon->getName(), playerPokemon->getHp(), playerPokemon->getMaxHp());
        info.opponentPokemon = CombatPokemonInfo(opponentPokemon->getName(), opponentPokemon->getHp(), opponentPokemon->getMaxHp());

        return info;
    }


    /**
     * @brief Récupère les informations sur le Pokémon en combat.
     * @param player true si on veut les informations du Pokémon du joueur, false pour l'adversaire.
     * @return Un objet CombatPokemonInfo contenant le nom, les points de vie actuels et les points de vie max du Pokémon.
     */
    CombatPokemonInfo CombatManager::getCombatPokemonInfo(bool player) const {
        Pokemon* pokemon;
        if (player) {
            pokemon = player_->getPokemon(playerPokemonIndex_);
        }
        else {
            pokemon = entraineur_->getPokemon(opponentPokemonIndex_);
        }

        return CombatPokemonInfo(pokemon->getName(), pokemon->getHp(), pokemon->getMaxHp());
    }


} // PokemonGame