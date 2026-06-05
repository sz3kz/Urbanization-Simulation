#pragma once
#include "Building.hpp"
#include <memory>

/**
 * @brief Wrapper around Building-derived classes' objects.
 *
 * A CellOccupant owns at most one Building instance via a
 * std::unique_ptr. Ownership can be transferred into and out of
 * the cell.
 *
 * An empty cell is represented by a nullptr occupant.
 */
struct CellOccupant
{
    /**
     * @brief Building currently occupying the cell.
     *
     * A nullptr value indicates that the cell is empty.
     */
    std::unique_ptr<Building> occupant;

    /**
     * @brief Constructs a cell (empty by default).
     *
     * This constructor is primarily used when BoardOccupants
     * initializes its contents.
     */
    CellOccupant()
      : occupant(nullptr)
    {
    }

    /**
     * @brief Constructs a cell containing a supplied building object.
     *
     * Ownership of the supplied building is transferred to the cell.
     *
     * @param building Building object to capture in the cell
     */
    explicit CellOccupant(std::unique_ptr<Building> building)
      : occupant(std::move(building))
    {
    }

    /**
     * @brief Releases the building object.
     *
     * Ownership is transferred to the caller and the cell becomes empty.
     *
     * @return Unique pointer owning the removed building, or nullptr
     *         if the cell was already empty.
     */
    auto release() -> std::unique_ptr<Building>;

    /**
     * @brief Returns a raw pointer to the contained building.
     *
     * Ownership remains with the cell.
     * Mostly used in context of polimorphism with Building * pointers.
     *
     * @return Pointer to the building, or nullptr if the cell is empty.
     */
    [[nodiscard]]
    auto getBuilding() const -> Building*;

    /**
     * @brief Checks whether the cell contains a building.
     *
     * @return true if the cell is empty
     * @return false if a building occupies the cell
     */
    [[nodiscard]]
    auto checkCellEmpty() const -> bool;

    /**
     * @brief Change a building's state based on current state.
     *
     * State transitions:
     * - NORMAL  -> RUIN
     * - BURNING -> RUIN
     * - RUIN    -> Building removed from the cell
     *
     * If the building is removed, ownership is discarded and the
     * cell becomes empty.
     *
     * @warning The cell must contain a building.
     */
    void transformState();

    /**
     *
     *
     * @param os Output stream.
     * @param building Building to render.
     * @return Reference to the output stream.
     */
    /**
     * @brief Genius-Level operator<< overloading for nice output syntax.
     *
     * Output depends on the current building state:
     * - RUIN    -> Derelict house emoji
     * - BURNING -> Fire emoji
     * - NORMAL  -> Building-specific emoji
     *
     * @param os Output stream
     * @param cell_occupant pointer to building object
     * @return Reference to the output stream.
     */
    friend auto operator<<(std::ostream& os, CellOccupant const& cell_occupant) -> std::ostream&;
};