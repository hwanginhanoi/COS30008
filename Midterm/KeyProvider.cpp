#include "KeyProvider.h"
#include <cctype>

KeyProvider::KeyProvider(const std::string& aKeyword) : fSize(aKeyword.length()), fKeyword(new char[fSize]), fIndex(0) {
    initialize(aKeyword);
}

KeyProvider::~KeyProvider() {
    delete[] fKeyword;
}

void KeyProvider::initialize(const std::string& aKeyword) {
    delete[] fKeyword;
    fSize = aKeyword.length();
    fKeyword = new char[fSize];
    fIndex = 0;

    for (size_t i = 0; i < fSize; ++i) {
        fKeyword[i] = std::toupper(aKeyword[i]);
    }
}

char KeyProvider::operator*() const {
    return fKeyword[fIndex];
}

KeyProvider& KeyProvider::operator<<(char aKeyCharacter) {
    if (std::isalpha(aKeyCharacter)) {
        fKeyword[fIndex] = std::toupper(aKeyCharacter);
        fIndex = (fIndex + 1) % fSize; // Circular buffer
    }
    return *this;
}
