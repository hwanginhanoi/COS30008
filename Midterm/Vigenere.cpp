#include "Vigenere.h"
#include <cctype>

Vigenere::Vigenere(const std::string& aKeyword) : fKeyword(aKeyword), fKeywordProvider(aKeyword) {
    initializeTable();
}

void Vigenere::initializeTable() {
    for (char row = 0; row < CHARACTERS; row++) {
        char lChar = 'B' + row;
        for (char column = 0; column < CHARACTERS; column++) {
            if (lChar > 'Z') lChar = 'A';
            fMappingTable[row][column] = lChar++;
        }
    }
}

std::string Vigenere::getCurrentKeyword() {
    std::string currentKeyword;
    for (size_t i = 0; i < fKeyword.length(); i++) {
        currentKeyword += *fKeywordProvider;
        fKeywordProvider << *fKeywordProvider;
    }
    return currentKeyword;
}

void Vigenere::reset() {
    fKeywordProvider.initialize(fKeyword);
}

char Vigenere::encode(char aCharacter) {
    if (std::isalpha(aCharacter)) {
        char base = 'A';
        bool isLower = std::islower(aCharacter);
        char encoded = fMappingTable[*fKeywordProvider - base][std::toupper(aCharacter) - base];

        fKeywordProvider << aCharacter;
        if (isLower) {
            return std::tolower(encoded);
        }
        return encoded;
    }
    else {
        return aCharacter;
    }
}

char Vigenere::decode(char aCharacter) {
    if (std::isalpha(aCharacter)) {
        char base = std::islower(aCharacter) ? 'a' : 'A';
        bool isLower = std::islower(aCharacter);
        char encoded = std::toupper(aCharacter);
        char decoded = 0;

        for (char column = 0; column < CHARACTERS; ++column) {
            if (fMappingTable[*fKeywordProvider - 'A'][column] == encoded) {
                decoded = column + base;
                break;
            }
        }

        fKeywordProvider << decoded;

        return isLower ? std::tolower(decoded) : decoded;
    }
    else {
        return aCharacter;
    }
}
