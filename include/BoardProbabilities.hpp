#pragma once
#include "Board.hpp"
#include "BoardOccupants.hpp"
#include "CellProbabilities.hpp"

/**
 * @brief Board made specifically for holding CellProbabilities(probabilities).
 *
 * This class extends Board<T> by defining its template type and by
 * providing helper functions for managing cell event probabilities.
 *
 * Each probability stores both a numeric value and the iteration
 * during which it was last computed. This allows for determination
 * whether a probability has already been calculated for a given
 * simulation iteration, which is utilized in probability propagation
 * algorithms of Building-derived classes.
 */
class BoardProbabilities : public Board<CellProbabilities>
{
    /**
     * @brief Inherit constructors from Board (we need da height & width).
     */
    using Board<CellProbabilities>::Board;

  public:
    /**
     * @brief Checks whether a probability was modified during current iteration.
     *
     * If the value of the last iteration the probability was updated at matches with
     * the current iteration -> probability was modified.
     *
     * @param coordinates Coordinates of interest
     * @param probability_type Probability type of interest
     * @param current_iteration Current iteration value
     *
     * @return true if the probability was updated during the specified
     *         iteration
     * @return false if otherwise
     *
     * @warning Does not check if Coordinates correspond to valid cell on board.
     * Will not error handle.
     */
    [[nodiscard]]
    auto checkProbabilityTypePercentageIsSetAtCoordinates(Coordinates const& coordinates,
                                                          ProbabilityType probability_type,
                                                          unsigned long current_iteration) const
      -> bool;

    /**
     * @brief Classic getter for the value of a probability type in a cell.
     *
     * @param coordinates Coordinates of interest
     * @param probability_type Probability type of interest
     *
     * @return The value
     *
     * @warning Does not check if Coordinates correspond to valid cell on board.
     * Will not error handle.
     * @warning We expect all valid probability types to be registered
     */
    [[nodiscard]]
    auto getProbabilityTypePercentageAtCoordinates(Coordinates const& coordinates,
                                                   ProbabilityType probability_type) -> double;

    /**
     * @brief Classic setter for the value of a probability type in a cell.
     *
     * The value of last iteration where probability of specified type was modified
     * is updated ofc.
     *
     * @param coordinates Coordinates of interest
     * @param probability_type Probability type of interest
     * @param current_iteration Iteration during which the value was computed.
     * @param percentage Probability value to store.
     *
     * @warning Does not check if Coordinates correspond to valid cell on board.
     * Will not error handle.
     * @warning We expect all valid probability types to be registered
     */
    void setProbabilityTypePercentageAtCoordinates(Coordinates const& coordinates,
                                                   ProbabilityType probability_type,
                                                   unsigned long current_iteration,
                                                   double percentage);

    /**
     * @brief Resets all probability cells to prepare for next iteration.
     *
     * For every coordinate:
     * - Empty occupant cells are initialized with probabilities of CellState::Empty.
     * - Occupied cells are initialized with probabilities of CellState::Occupied.
     *
     * Existing probability values are discarded and replaced with
     * freshly initialized CellProbabilities instances.
     * Is okay, unique_ptr prevents a memory leak.
     *
     * @param occupants Current board state used to decide if specific cell is
     * empty or occupied
     *
     * @warning The occupants must logically link to this board(same width & height),
     * otherwise is nonsense.
     */
    void resetProbabilities(BoardOccupants const& occupants);
};