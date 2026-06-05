#pragma once
#include "CellProbabilities.hpp"
#include "Coordinates.hpp"
#include "State.hpp"
#include "World.hpp"
#include <functional>
#include <memory>

// virtual <return-type> func(<parameters>) = 0
//  Pure virtual function: don't implement it here, force implementation at child,
//  disallow direct Building object instantiation.

class Building
{
    std::string emoji{ "❌" };
    unsigned int radius;
    std::unique_ptr<State> building_state;

  public:
    Building(unsigned int radius)
      : radius(radius)
      , building_state(std::make_unique<State>()) {};
    /* Virtual destructor
     * Can aid in child class identification via dynamic_cast.
     * Since we use the Building::getBuildingType() function to identify child classes
     *  this is not really needed
     */
    virtual ~Building() = default;

    /* Disable all other special methods*/
    Building(Building const&) = delete;
    auto operator=(Building const&) -> Building& = delete;
    Building(Building&&) = delete;
    auto operator=(Building&&) -> Building& = delete;

    [[nodiscard]]
    virtual auto getBuildingType() const -> BuildingType = 0;

    [[nodiscard]]
    auto getRadius() const -> unsigned int
    {
        return this->radius;
    }

    [[nodiscard]]
    auto getBuildingState() const -> BuildingState
    {
        return this->building_state->getBuildingState();
    }
    void setBuildingState(const BuildingState supplied_building_state) const
    {
        this->building_state->setBuildingState(supplied_building_state);
    }

    [[nodiscard]]
    auto getTimeToLive() const -> unsigned int
    {
        return this->building_state->getTimeToLive();
    }

    void decay() const { this->building_state->doDecay(); }

    void resetTimeToLive() const { this->building_state->resetTimeToLive(); }
    void setEmoji(std::string const& supplied_emoji) { this->emoji = supplied_emoji; }

    // Function that populates probability_board with probabilities
    virtual void applyProbabilities(
      [[maybe_unused]] std::function<bool(Coordinates)> askCellExistsAtCoordinates,
      [[maybe_unused]] std::function<bool(Coordinates)> askCellEmptyAtCoordinates,
      [[maybe_unused]] std::function<bool(Coordinates, ProbabilityType)>
        askProbabilityTypePercentageIsSetAtCoordinates,
      [[maybe_unused]] std::function<double(Coordinates, ProbabilityType)>
        askProbabilityTypePercentageAtCoordinates,
      [[maybe_unused]] std::function<void(Coordinates, ProbabilityType, double)>
        setCellPercentageOfProbabilityAtCoordinates,
      [[maybe_unused]] std::function<bool(Coordinates, BuildingState)>
        askBuildingAtCoordinatesIsInState) = 0;
    friend auto operator<<(std::ostream& os, const Building& building) -> std::ostream&;
};
