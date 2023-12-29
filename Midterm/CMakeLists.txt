cmake_minimum_required(VERSION 3.26)
project(Midterm)

set(CMAKE_CXX_STANDARD 23)

add_executable(Midterm main.cpp
        KeyProvider.h
        KeyProvider.cpp
        Vigenere.h
        Vigenere.cpp
        VigenereForwardIterator.h
        iVigenereStream.h
        iVigenereStream.cpp
        VigenereForwardIterator.cpp
)
