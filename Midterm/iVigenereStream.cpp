#include "iVigenereStream.h"
#include <iostream>

iVigenereStream::iVigenereStream(Cipher aCipher, const std::string& aKeyword, const char* aFileName)
        : fCipher(aCipher), fCipherProvider(aKeyword), fIStream(std::ifstream()) {
    if (aFileName != nullptr) {
        open(aFileName);
    }
}

iVigenereStream::~iVigenereStream() {
    close();
}

void iVigenereStream::open(const char* aFileName) {
    fIStream.open(aFileName, std::ios::binary);
}

void iVigenereStream::close() {
    fIStream.close();
}

void iVigenereStream::reset() {
    seekstart();
    fCipherProvider.reset();
}

bool iVigenereStream::good() const {
    return fIStream.good();
}

bool iVigenereStream::is_open() const {
    return fIStream.is_open();
}

bool iVigenereStream::eof() const {
    return fIStream.eof();
}

iVigenereStream& iVigenereStream::operator>>(char& aCharacter) {
    if (!eof()) {
        aCharacter = fCipher(fCipherProvider, (char)fIStream.get());
    }
    return *this;
}