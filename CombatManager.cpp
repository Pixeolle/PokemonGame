//
// Created by olbnf on 17/04/2025.
//
#include <iostream>

#include "CombatManager.h"

namespace PokemonGame {

    CombatManager::CombatManager() : typeManager_(TypeManager::getInstance()), playerPokemonIndex_(0), opponentPokemonIndex_(0) {}

    int CombatManager::checkCombatEnd() const {

        if (trainerKO(player_)) {
            return -1;
        }

        if (trainerKO(entraineur_)) {
            return 1;
        }

        return 0;
    }

    bool CombatManager::trainerKO(Entraineur* trainer) {
        for (const auto& pokemon : trainer->getPokemonTeam()) {
            if (pokemon->getHp() != 0) {
                return false;
            }
        }
        return true;
    }

    void CombatManager::startCombat(Joueur *player, Entraineur *opponent) {
        player_ = player;
        entraineur_ = opponent;
        playerPokemonIndex_ = 0;
        opponentPokemonIndex_ = 0;
    }

    TurnInfo CombatManager::playerTurn() {
        TurnInfo info;
        Pokemon* playerPokemon = player_->getPokemon(playerPokemonIndex_);
        Pokemon* opponentPokemon = entraineur_->getPokemon(opponentPokemonIndex_);
        int damage = playerPokemon->getAttackPower();


        info.messages.push_back(playerPokemon->getName() + " attaque " + playerPokemon->getAttackName());
        float multiplier = typeManager_.getMultiplier(playerPokemon->getTypes(), opponentPokemon->getTypes());
        int totalDamage = damage;
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
            }
        }

        info.playerPokemon = CombatPokemonInfo(playerPokemon->getName(), playerPokemon->getHp(), playerPokemon->getMaxHp());
        info.opponentPokemon = CombatPokemonInfo(opponentPokemon->getName(), opponentPokemon->getHp(), opponentPokemon->getMaxHp());

        return info;
    }

    TurnInfo CombatManager::opponentTurn() {
        TurnInfo info;
        Pokemon* playerPokemon = player_->getPokemon(playerPokemonIndex_);
        Pokemon* opponentPokemon = entraineur_->getPokemon(opponentPokemonIndex_);
        int damage = playerPokemon->getAttackPower();

        info.messages.push_back(opponentPokemon->getName() + " attaque " + opponentPokemon->getAttackName());
        float multiplier = typeManager_.getMultiplier(opponentPokemon->getTypes(), playerPokemon->getTypes());
        int totalDamage = damage;

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