#pragma once

#include <cstdint>

/**
 * @brief Command-line argument positions.
 *
 * This enumeration provides named indices for accessing values
 * in the argv array passed to main().
 *
 * Expected command-line syntax:
 * @code
 * ./program <width> <height> <random-seed> <output-filename>
 * @endcode
 */
enum class ArgumentType : std::uint8_t
{
    /**
     * @brief Program executable name.
     *
     * Corresponds to argv[0].
     */
    EXEC_NAME,

    /**
     * @brief Board width argument.
     *
     * Corresponds to argv[1].
     */
    WIDTH,

    /**
     * @brief Board height argument.
     *
     * Corresponds to argv[2].
     */
    HEIGHT,

    /**
     * @brief Random seed argument.
     *
     * Corresponds to argv[3].
     */
    SEED,

    /**
     * @brief Output filename argument.
     *
     * Corresponds to argv[4].
     */
    OUTPUT_FILENAME,

    /**
     * @brief Expected argument count.
     *
     * Used to validate argc before processing arguments.
     * The expected value is 5:
     * - executable name
     * - width
     * - height
     * - random seed
     * - output filename
     */
    ARGS,
};

/**
 * @brief Prints command-line usage information.
 *
 * @param name Program executable name.
 */
void usage(const char* name);

/**
 * @brief Entry point of the simulation application.
 *
 * Validates command-line arguments, initializes locale support
 * for Unicode emoji output, constructs a Simulation instance,
 * and starts the simulation loop.
 *
 * Expected arguments:
 * @code
 * ./program <width> <height> <random-seed> <output-filename>
 * @endcode
 *
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line argument strings.
 * @return 0 on normal termination.
 * @return -1 if argument validation fails.
 */
auto main(int argc, char* argv[]) -> int;