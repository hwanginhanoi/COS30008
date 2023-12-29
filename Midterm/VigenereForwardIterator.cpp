#include "VigenereForwardIterator.h"

VigenereForwardIterator::VigenereForwardIterator(iVigenereStream& aIStream)
        : fIStream(aIStream), fEOF(false) {
    // Initialize the iterator, set fCurrentChar to the first character
    operator++(); // Call the prefix increment to read the first character
}

char VigenereForwardIterator::operator*() const {
    return fCurrentChar;
}

VigenereForwardIterator& VigenereForwardIterator::operator++() {
    char nextChar;
    if (fIStream >> nextChar) {
        fCurrentChar = nextChar;
    } else {
        fEOF = true;
    }
    return *this;
}

VigenereForwardIterator VigenereForwardIterator::operator++(int) {
    VigenereForwardIterator temp = *this;
    ++(*this);
    return temp;
}

bool VigenereForwardIterator::operator==(const VigenereForwardIterator& aOther) const {
    return &fIStream == &aOther.fIStream && fEOF == aOther.fEOF;
}

bool VigenereForwardIterator::operator!=(const VigenereForwardIterator& aOther) const {
    return !(*this == aOther);
}

VigenereForwardIterator VigenereForwardIterator::begin() const {
    VigenereForwardIterator beginIterator = *this; // Copy the current iterator
    beginIterator.fIStream.reset(); // Reset the stream
    beginIterator.operator++(); // Read the first character
    return beginIterator;
}

VigenereForwardIterator VigenereForwardIterator::end() const {
    VigenereForwardIterator endIterator = *this; // Copy the current iterator
    endIterator.fEOF = true; // Set fEOF to true
    return endIterator;
}
