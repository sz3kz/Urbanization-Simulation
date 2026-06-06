#pragma once
#include "BoardOccupants.hpp"
#include "BoardProbabilities.hpp"

#include <chrono>
#include <random>
#include <string>
#include <utility>

/**
 * @brief Runs the urban simulation.
 *
 * The simulation maintains three board representations:
 * - previous_board: current urban building situashion.
 * - probability_board: probabilities for every cell corresponding to building boards.
 * - next_board: next urban building situashion.
 *
 * Each iteration performs the following steps:
 * 1. Propagate building effects into the probability board.
 * 2. Execute probabilistic events.
 * 3. Decay buildings and transform states when necessary.
 * 4. Recycle board buffers.
 * 5. Reset probability values.
 * 6. Print the current board state.
 */
class Simulation
{
    /**
     * @brief Output file used to store simulation snapshiots
     */
    std::string filename;

    /**
     * @brief Current simulation iteration.
     */
    unsigned long current_iteration{ 0 };

    /**
     * @brief Current board state.
     */
    BoardOccupants previous_board;

    /**
     * @brief Probability values generated during an iteration.
     */
    BoardProbabilities probability_board;

    /**
     * @brief Next board state under construction.
     */
    BoardOccupants next_board;

    /**
     * @brief Random number generator used for probability rolls.
     */
    std::mt19937 generator;

    /**
     * @brief Advances the simulation iteration counter.
     */
    void incrementIteration();

    /**
     * @brief Suspends execution for a specified duration.
     *
     * @param timespan Duration to sleep.
     */
    static void sleep(std::chrono::milliseconds timespan);

    /**
     * @brief Moves all occupants from the next board into the previous board.
     *
     * Ownership of all buildings is transferred from next_board
     * to previous_board.
     */
    void recycleBoards();

    /**
     * @brief Executes all probabilities stored in the probability board.
     *
     * This stage may:
     * - Create new buildings.
     * - Ignite buildings.
     * - Restore ruined buildings.
     * - Restore building time-to-live values.
     */
    void executeProbability();

    /**
     * @brief Applies building-specific probability effects.
     *
     * Iterates through all buildings on the board and invokes
     * their Building::applyProbabilities() implementation.
     */
    void propagateBuildingProbabilities();

    /**
     * @brief Applies decay to all buildings.
     *
     * Buildings whose time-to-live falls below the decay threshold
     * undergo a state transition. Otherwise their lifetime is reduced.
     */
    void decayBuildings();

    /**
     * @brief Writes the current board state to the console and file.
     *
     * @param file Output file stream.
     */
    void print(std::ofstream& file) const;

    /**
     * @brief Performs a probabilistic roll.
     *
     * Uses a Bernoulli distribution to determine whether an event
     * occurs.
     *
     * @param percentage Probability value in the range [0.0, 1.0].
     * @return true if the event occurs.
     * @return false otherwise.
     */
    auto rollProbabilityDice(double percentage) -> bool;

  public:
    /**
     * @brief Constructs a simulation.
     *
     * Initializes all board buffers and seeds the random
     * number generator.
     *
     * @param width Board width.
     * @param height Board height.
     * @param random_seed Seed used for random event generation.
     * @param filename Output file used to store simulation snapshots.
     */
    Simulation(unsigned int width,
               unsigned int height,
               unsigned int random_seed,
               std::string filename)
      : filename(std::move(filename))
      , previous_board(width, height)
      , probability_board(width, height)
      , next_board(width, height)
      , generator(random_seed)
    {
    }

    /**
     * @brief Starts the simulation loop.
     *
     * Runs indefinitely until the program is terminated.
     *
     * @note This function never returns.
     */
    [[noreturn]]
    void run();
};