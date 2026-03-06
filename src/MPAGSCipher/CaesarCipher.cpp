#include "CaesarCipher.hpp"
#include "Alphabet.hpp"

#include <iostream>
#include <string>

/**
 * \file CaesarCipher.cpp
 * \brief Contains the implementation of the CaesarCipher class
 */

CaesarCipher::CaesarCipher(const std::size_t key) : key_{key % Alphabet::size}
{
}

CaesarCipher::CaesarCipher(const std::string& key) : key_{0}
{
    // We have the key as a string, but the Caesar cipher needs an unsigned long, so we first need to convert it
    // We default to having a key of 0, i.e. no encryption, if no (valid) key was provided on the command line
    if (!key.empty()) {
        // Before doing the conversion we should check that the string contains a
        // valid positive integer.
        try {
            key_ = std::stoul(key) % Alphabet::size;
        }    // catch not an integer
        catch (const std::invalid_argument& e) {
            throw InvalidKey{
                "Key for Caesar cipher must be an unsigned long integer, the supplied key (" +
                key +
                ") could not be successfully converted to a numeric value."};
        }    // catch out of range (too large to fit in an unsigned long)
        catch (const std::out_of_range& e) {
            throw InvalidKey{
                "Key for Caesar cipher must be an unsigned long integer for Caesar cipher,\n"
                "        the supplied key (" +
                key +
                ") could not be successfully converted as it is out of range."};
        }
    } else {
        throw InvalidKey{"Key for Caesar cipher must be non-empty."};
    }
}

std::string CaesarCipher::applyCipher(const std::string& inputText,
                                      const CipherMode cipherMode) const
{
    // Create the output string
    std::string outputText;

    // Loop over the input text
    char processedChar{'x'};
    for (const auto& origChar : inputText) {
        // For each character in the input text, find the corresponding position in
        // the alphabet by using an indexed loop over the alphabet container
        for (std::size_t i{0}; i < Alphabet::size; ++i) {
            if (origChar == Alphabet::alphabet[i]) {
                // Apply the appropriate shift (depending on whether we're encrypting
                // or decrypting) and determine the new character
                // Can then break out of the loop over the alphabet
                switch (cipherMode) {
                    case CipherMode::Encrypt:
                        processedChar =
                            Alphabet::alphabet[(i + key_) % Alphabet::size];
                        break;
                    case CipherMode::Decrypt:
                        processedChar =
                            Alphabet::alphabet[(i + Alphabet::size - key_) %
                                               Alphabet::size];
                        break;
                }
                break;
            }
        }

        // Add the new character to the output text
        outputText += processedChar;
    }

    return outputText;
}
