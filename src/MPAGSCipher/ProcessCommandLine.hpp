#ifndef MPAGSCIPHER_PROCESSCOMMANDLINE_HPP
#define MPAGSCIPHER_PROCESSCOMMANDLINE_HPP

#include "CipherMode.hpp"
#include "CipherType.hpp"

#include <stdexcept>
#include <string>
#include <vector>

/**
 * \file ProcessCommandLine.hpp
 * \brief Contains the declarations of the function for processing the command-line arguments and the data structure used to hold the resulting settings
 */

/**
 * \struct ProgramSettings
 * \brief Holds the settings of the program that can be modified by command-line arguments
 */
struct ProgramSettings {
    /// Indicates the presence of the help flag in the arguments
    bool helpRequested{false};
    /// Indicates the presence of the version flag in the arguments
    bool versionRequested{false};
    /// Name of the input file
    std::string inputFile;
    /// Name of the output file
    std::string outputFile;
    /// Key to be used in encrypting/decrypting routine
    std::vector<std::string> cipherKey;
    /// Which cipher(s) to use (e.g. Caesar, Playfair, etc.)
    std::vector<CipherType> cipherType;
    /// Flag indicating the mode in which the cipher should run (i.e. encrypt or decrypt)
    CipherMode cipherMode{CipherMode::Encrypt};
};

/**
 * \brief Processes the command-line arguments and modifies accordingly the program settings
 *
 * \param cmdLineArgs The command-line arguments to be processed
 * \param settings The program settings to be set according to the result of the processing
 * \return 0 if the processing was successful, 1 if there was an error in the processing
 * 
 * \exception MissingArgument if an argument that requires a value is missing
 * \exception UnknownArgument if an unrecognised argument is supplied
 * \exception InconsistentCipherNumber if the number of ciphers specified by the 
 * --multi-cipher argument is inconsistent with the number of ciphers specified by the -c argument
 */
bool processCommandLine(const std::vector<std::string>& cmdLineArgs,
                        ProgramSettings& settings);

/**
 * \brief Custom exception for missing argument in the command line
 */
class MissingArgument : public std::invalid_argument {
  public:
    MissingArgument(const std::string& msg) : std::invalid_argument{msg} {}
};

/**
 * \brief Custom exception for unknown argument in the command line
 */
class UnknownArgument : public std::invalid_argument {
  public:
    UnknownArgument(const std::string& msg) : std::invalid_argument{msg} {}
};

/**
 * \brief Custom exception for invalid number of ciphers
 */
class InconsistentCipherNumber : public std::invalid_argument {
  public:
    InconsistentCipherNumber(const std::string& msg) :
        std::invalid_argument{msg}
    {
    }
};

#endif    // MPAGSCIPHER_PROCESSCOMMANDLINE_HPP
