/**
 * @file logger.hpp
 * @author Max Heinekamp
 * @brief Contains LOGGER class
 * @version 1.0
 * @date 25-07-2023
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#ifndef PAIRWISE_LOGGER
#define PAIRWISE_LOGGER

#include <iostream>
#include <string>

/**
 * @brief only prints Status Messages if Verbose Mode is enabled
 */
class LOGGER {
private:
    /**
     * @brief If true, status messages will be logged to the console
     */
    static bool verboseMode;

public:
    /**
     * @brief Set the Verbose Mode object
     * 
     * @param verbose set to true to enable output of status messages
     */
    static void SetVerboseMode(bool verbose) {
        verboseMode = verbose;
    }

    template <typename T>
    /**
     * @brief Replaces std::cout, only prints if logging is enabled
     * 
     * @param message message to be printed (just replace std::cout with LOGGER::cout)
     */
    LOGGER& operator<<(const T& message) {
        if (verboseMode) {
            std::cout << message;
        }
        return *this;
    }

    // Support for manipulators like std::endl
    typedef std::ostream& (*Manipulator)(std::ostream&);
    LOGGER& operator<<(Manipulator manip) {
        if (verboseMode) {
            std::cout << manip;
        }
        return *this;
    }
};

#endif // LOGGER_H
