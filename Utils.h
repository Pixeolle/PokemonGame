//
// Created by olbnf on 17/04/2025.
//

#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>

namespace PokemonGame::Utils::String {

    [[nodiscard]] std::string toTitle(std::string str);

    [[nodiscard]] std::string trim(std::string str);

    [[nodiscard]] std::string trimValidate(const std::string& imput, const std::string& fieldName);

    [[nodiscard]] std::string trimValidateTitle(const std::string& input, const std::string& fieldName);

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
