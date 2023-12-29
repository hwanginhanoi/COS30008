#pragma once
#include "KeyProvider.h"
#define CHARACTERS 26

class Vigenere {
private:
    char fMappingTable[CHARACTERS][CHARACTERS]{};
    const std::string fKeyword;
    KeyProvider fKeywordProvider;

    // Initialize the mapping table
    void initializeTable();

public:
    // Initialize Vigenere scrambler
    Vigenere(const std::string& aKeyword);

    // Return the current keyword
    std::string getCurrentKeyword();

    // Reset Vigenere scrambler
    void reset();

    // Encode a character using the current keyword character and update keyword
    char encode(char aCharacter);

    // Decode a character using the current keyword character and update keyword
    char decode(char aCharacter);
};
