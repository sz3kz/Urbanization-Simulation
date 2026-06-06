#pragma once
#include "Board.hpp"
#include "Building.hpp"
#include "CellOccupant.hpp"
#include <iostream>

/**
 * @brief Board made specifically for holding CellOccupants(buildings).
 *
 * This class extends Board<T> by defining its template type and by
 * providing helper functions for managing building ownership within cells.
 * Buildings are stored with ownership via smart pointers.
 *
 * Each cell may either be empty or contain exactly one Building-derived
 * object.
 */
class BoardOccupants : public Board<CellOccupant>
{
  public:
    /**
     * @brief Inherit constructors from Board (we need da height & width).
     */
    using Board<CellOccupant>::Board;

    /**
     * @brief Checks whether a cell is occupied (has a building in it)
     *
     * @param coordinates Coordinates of interest
     * @return true if the cell does not contain a building
     * @return false if the cell contains a building
     *
     * @warning Does not check if Coordinates correspond to valid cell on board.
     * Will not error handle.
     */
    [[nodiscard]]
    auto checkCellEmptyAtCoordinates(Coordinates const& coordinates) const -> bool;

    /**
     * @brief Releases building at coordinates and returns it.
     *
     * Ownership of the building is returned as a unique_ptr. Cell is emptied in
     * the process.
     *
     * @param coordinates Coordinates of interest
     * @return Unique pointer owning the removed building, or nullptr
     *         if the cell was already empty
     *
     * @warning Does not check if Coordinates correspond to valid cell on board.
     * Will not error handle.
     */
    auto releaseOccupantAtCoordinates(Coordinates const& coordinates) -> std::unique_ptr<Building>;

    /**
     * @brief Acquires building to specified coordinates.
     *
     * Cell is populated with unique_ptr-ownership of the specific buidling.
     *
     * @param coordinates Coordinates of interest
     * @param building Building to insert into the board
     *
     * @warning Does not check if Coordinates correspond to valid cell on board.
     * Will not error handle.
     * @arning Any existing occupant in the cell will be overwritten
     * Is okay, unique_ptr prevents a memory leak.
     */
    void acquireOccupantToCoordinates(Coordinates const& coordinates,
                                      std::unique_ptr<Building> building);

    /**
     * @brief Retrieves the specified coordinate's cell's building type
     *
     * @param coordinates Coordinates of interest
     * @return Type of the building occupying the cell
     *
     * @warning Does not check if Coordinates correspond to valid cell on board.
     * Will not error handle.
     * @warning The cell must contain a building. Check first.
     */
    [[nodiscard]]
    auto getCellBuildingType(Coordinates const& coordinates) const -> BuildingType;

    /**
     * @brief Genius-Level operator<< overloading for nice output syntax.
     *
     * Outputs every cell one by one with added newlines where row stops
     *
     * @param os Output stream
     * @param board Board to print
     * @return Reference to the output stream
     */
    friend auto operator<<(std::ostream& os, BoardOccupants const& board) -> std::ostream&;
};