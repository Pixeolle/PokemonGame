//
// Created by olbnf on 17/04/2025.
//

#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <filesystem>

#include "Utils.h"

namespace PokemonGame::Utils {

    std::string String::toTitle(std::string str) {
        for (int i = 0; i < str.length(); i++) {
            if (i == 0 || str[i - 1] == ' ') {
                str[i] = static_cast<char>(std::toupper(static_cast<unsigned char>(str[i])));
            }
            else {
                str[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(str[i])));
            }
        }

        return str;
    }

    std::string String::trim(std::string str) {
        auto start = str.begin();
        while (start != str.end() && std::isspace(*start)) {
            ++start;
        }

        auto end = str.end();
        do {
            --end;
        } while (std::distance(start, end) > 0 && std::isspace(*end));

        return std::string(start, end + 1);
    }

    std::string String::trimValidate(const std::string& input, const std::string& fieldName) {
        std::string trimmed = trim(input);
        if (trimmed.empty()) {
            throw std::invalid_argument("Le " + fieldName + " ne peut pas être vide ou uniquement des espaces.");
        }

        return trimmed;
    }

    std::string String::trimValidateTitle(const std::string& input, const std::string& fieldName) {
        std::string trimmed = trim(input);
        if (trimmed.empty()) {
            throw std::invalid_argument("Le " + fieldName + " ne peut pas être vide ou uniquement des espaces.");
        }

        return toTitle(trimmed);
    }

    void String::promptAndValidatePath(const std::string& prompt, const std::string& defaultPath, std::string& resultPath, int boxWidth) {
        std::string inputPath;
        bool pathIsValid = false;

        while (!pathIsValid) {
            Display::printInBox(prompt, boxWidth);
            Display::printInBox("[Défaut: " + defaultPath + "]", boxWidth);
            Display::printInBox("Entrez le chemin (ou laissez vide pour défaut):", boxWidth);
            Display::drawBoxLine("├", "─", "┤", boxWidth);
            std::cout << "│ > ";

            if (std::getline(std::cin, inputPath)) {
                if (inputPath.empty()) {
                    resultPath = defaultPath;
                    Display::printInBox("-> Utilisation du chemin par défaut.", boxWidth);

                } else {
                    resultPath = inputPath;
                    Display::printInBox("-> Chemin saisi: " + resultPath, boxWidth);
                }

                if (std::filesystem::exists(resultPath)) {
                     std::cout << "│ " << "\033[32m" << "[OK] Fichier trouvé." << "\033[0m" << std::left << std::setw(boxWidth - 23) << "" << "│" << std::endl; // Vert
                    pathIsValid = true;
                } else {
                    std::cout << "│ " << "\033[31m" << "[ERREUR] Fichier non trouvé : " << resultPath << "\033[0m" << std::left << std::setw(boxWidth - 33 - resultPath.length()) << "" << "│" << std::endl; // Rouge

                }
            } else {
                 throw std::invalid_argument("Erreur de lecture de l'entrée.");
            }
            Display::drawBoxLine("├", "─", "┤", boxWidth);
        }
    }

    #ifdef _WIN32
    #include <windows.h>
        void Display::clearConsole() {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            COORD coordScreen = { 0, 0 };
            DWORD cCharsWritten;
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            DWORD dwConSize;
            if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
            dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
            if (!FillConsoleOutputCharacter(hConsole, (TCHAR)' ', dwConSize, coordScreen, &cCharsWritten)) return;
            if (!GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
            if (!FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten)) return;
            SetConsoleCursorPosition(hConsole, coordScreen);
        }

        int Display::getConsoleWidth() {
            CONSOLE_SCREEN_BUFFER_INFO csbi;
            if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi)) {
                return csbi.srWindow.Right - csbi.srWindow.Left + 1;
            }
            return 80;
        }

    #else
    #include <cstdlib>
    #include <sys/ioctl.h>
    #include <unistd.h>

        void Display::clearConsole() {
            std::cout << "\033[2J\033[H" << std::flush;
        }

        int Display::getConsoleWidth() {
            struct winsize size;
            if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &size) == 0) {
                return size.ws_col;
            }
            return 80;
        }

    #endif

    void Display::printCentered(const std::string& text) {
        int consoleWidth = Display::getConsoleWidth();
        int textLength = text.length();
        int padding = (consoleWidth - textLength) / 2;
        if (padding < 0) padding = 0;

        std::cout << std::setw(padding) << "" << text << std::endl;
    }

    void Display::drawBoxLine(const std::string& start, const std::string& middle, const std::string& end, int width, bool endLine) {

        if (middle.empty()) {
            throw std::invalid_argument("Le caractère du milieu ne peut pas être vide dans drawBoxLine.");
        }

        if (width < 2) {
            if (width == 1) std::cout << start;
            std::cout << std::endl;
            return;
        }

        std::cout << start;
        for (int i = 0; i < width - 2; ++i) {
            std::cout << middle;
        }
        std::cout << end;
        if (endLine) {
            std::cout << std::endl;
        }
    }

    void Display::printInBox(const std::string& text, int boxWidth, bool deleteBeginSpace, bool endLine) {
        int availableWidth = boxWidth - 4;
        int currentByteIndex = 0;
        int currentLineCharCount = 0;

        std::cout << "| ";

        while (currentByteIndex < text.length()) {
            std::string nextCharStr;
            size_t nextCharByteSize = 0;
            size_t charLogicalIndex = 0;

            size_t tempByteIndex = 0;
            size_t tempCharIndex = 0;
            while(tempByteIndex < currentByteIndex && tempByteIndex < text.length()){
                 unsigned char c = text[tempByteIndex];
                 size_t advance = 0;
                 if ((c & 0x80) == 0) advance = 1;
                 else if ((c & 0xE0) == 0xC0) advance = 2;
                 else if ((c & 0xF0) == 0xE0) advance = 3;
                 else if ((c & 0xF8) == 0xF0) advance = 4;
                 else advance = 1;
                 tempByteIndex += advance;
                 if (tempByteIndex > text.length()) tempByteIndex = text.length();
                 tempCharIndex++;
            }
            charLogicalIndex = tempCharIndex;


            std::tie(nextCharStr, nextCharByteSize) = getUtf8Char(text, charLogicalIndex);


            if (nextCharByteSize == 0) {
                break;
            }

            int nextCharDisplayWidth = 1;


            if (currentLineCharCount + nextCharDisplayWidth > availableWidth) {
                int padding = availableWidth - currentLineCharCount;
                std::cout << std::string(padding, ' ');
                std::cout << " |\n| ";
                currentLineCharCount = 0;
            }

            if ((nextCharStr != " " || currentLineCharCount != 0) || !deleteBeginSpace) {
                std::cout << nextCharStr;
                currentLineCharCount += nextCharDisplayWidth;
            }
            currentByteIndex += nextCharByteSize;
        }

        int lastLinePadding = availableWidth - currentLineCharCount;
        if (lastLinePadding < 0) lastLinePadding = 0;
        std::cout << std::string(lastLinePadding, ' ');
        std::cout << " |";
        if (endLine) {
            std::cout << std::endl;
        }
    }

    std::pair<std::string, size_t> Display::getUtf8Char(const std::string& s, size_t charIndex) {
        size_t byteIndex = 0;
        size_t currentCharlIndex = 0;
        while(byteIndex < s.length()) {
            if (currentCharlIndex == charIndex) {
                unsigned char c = s[byteIndex];
                size_t charByteSize = 0;
                if ((c & 0x80) == 0) charByteSize = 1;
                else if ((c & 0xE0) == 0xC0) charByteSize = 2;
                else if ((c & 0xF0) == 0xE0) charByteSize = 3;
                else if ((c & 0xF8) == 0xF0) charByteSize = 4;
                else charByteSize = 1;

                if (byteIndex + charByteSize > s.length()) charByteSize = s.length() - byteIndex;

                return {s.substr(byteIndex, charByteSize), charByteSize};
            }

            unsigned char c = s[byteIndex];
            size_t advance = 0;
            if ((c & 0x80) == 0) advance = 1;
            else if ((c & 0xE0) == 0xC0) advance = 2;
            else if ((c & 0xF0) == 0xE0) advance = 3;
            else if ((c & 0xF8) == 0xF0) advance = 4;
            else advance = 1;

            byteIndex += advance;
            if (byteIndex > s.length()) byteIndex = s.length();
            currentCharlIndex++;
        }
        return {"", 0};
    }

    int Display::estimateUtf8DisplayWidth(const std::string& text) {
        int width = 0;
        for (size_t i = 0; i < text.length();) {
            unsigned char c = text[i];
            width++;

            if ((c & 0x80) == 0) {
                i += 1;
            } else if ((c & 0xE0) == 0xC0) {
                i += 2;
            } else if ((c & 0xF0) == 0xE0) {
                i += 3;
            } else if ((c & 0xF8) == 0xF0) {
                i += 4;
            } else {
                i += 1;
            }
            if (i > text.length()) i = text.length();
        }
        return width;
    }

    void Display::displayBoxChoices(const std::string &prompt, const std::vector<std::string>& choices, int boxWidth, int select = 0) {

        drawBoxLine("┌", "─", "┐", boxWidth);
        printInBox(prompt, boxWidth);
        drawBoxLine("├", "─", "┤", boxWidth);
        for (int i = 0; i < choices.size(); i++) {
            printInBox(i == select ? "> " + choices[i] : "  " + choices[i], boxWidth, false);
        }
        drawBoxLine("└", "─", "┘", boxWidth);
    }


} // PokemonGame