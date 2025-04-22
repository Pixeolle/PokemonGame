//
// Created by olbnf on 17/04/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace PokemonGame::Utils::String {

    [[nodiscard]] std::string toTitle(std::string str);

    /**
     * @brief Supprime les espaces au début et à la fin d'une chaîne de caractères.
     * @param str La chaîne de caractères à traiter.
     * @return La chaîne sans espaces au début et à la fin.
     */
    [[nodiscard]] std::string trim(std::string str);

    /**
     * @brief Supprime les espaces d'une chaîne et valide qu'elle n'est pas vide.
     * @param imput La chaîne de caractères à traiter.
     * @param fieldName Le nom du champ pour le message d'erreur.
     * @return La chaîne sans espaces.
     * @throws std::invalid_argument Si la chaîne est vide après le traitement.
     */
    [[nodiscard]] std::string trimValidate(const std::string& imput, const std::string& fieldName);

    [[nodiscard]] std::string trimValidateTitle(const std::string& input, const std::string& fieldName);

    /**
     * @brief Demande et valide un chemin d'accès saisi par l'utilisateur.
     * @param prompt Le message à afficher pour demander le chemin.
     * @param defaultPath Le chemin par défaut à utiliser si l'utilisateur ne saisit rien.
     * @param resultPath La variable où stocker le chemin validé.
     * @param boxWidth La largeur de la boîte d'affichage.
     * @throws std::invalid_argument Si une erreur de lecture de l'entrée se produit.
     */
    void promptAndValidatePath(const std::string& prompt, const std::string& defaultPath, std::string& resultPath, int boxWidth);

} // PokemonGame

namespace PokemonGame::Utils::Display {

    void clearConsole();

    int getConsoleWidth();

    void printCentered(const std::string& text);

    void drawBoxLine(const std::string& start, const std::string& middle, const std::string& end, int width, bool endLine = true);

    void printInBox(const std::string& text, int boxWidth, bool deleteBeginSpace = true, bool endLine = true);

    std::pair<std::string, size_t> getUtf8Char(const std::string& s, size_t charIndex);

    int estimateUtf8DisplayWidth(const std::string& text);

    void displayBoxChoices(const std::string& prompt, const std::vector<std::string>& choices, int boxWidth, int select);

}

#endif //UTILS_H
