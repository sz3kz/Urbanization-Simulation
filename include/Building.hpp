#pragma once
#include "Coordinates.hpp"
#include "World.hpp"
#include <functional>
#include <string>

// virtual <return-type> func(<parameters>) = 0
//  Pure virtual function: don't implement it here, force implementation at child,
//  disallow direct Building object instantiation.

class Building
{
    unsigned int radius;
    unsigned int time_to_live{ normal_state_initial_time_to_live };
    BuildingState state_name{ BuildingState::NORMAL };

  public:
    Building(unsigned int radius)
      : radius(radius) {};
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
    auto getTimeToLive() const -> unsigned int
    {
        return this->time_to_live;
    };
    void setTimeToLive(unsigned int suppled_time_to_live)
    {
        this->time_to_live = suppled_time_to_live;
    };
    [[nodiscard]]
    auto getBuildingState() const -> BuildingState
    {
        return this->state_name;
    };
    [[nodiscard]]
    auto getRadius() const -> unsigned int
    {
        return this->radius;
    }

    void setBurning()
    {
        time_to_live = burning_state_initial_time_to_live;
        state_name = BuildingState::BURNING;
    };
    void setNormal()
    {
        time_to_live = normal_state_initial_time_to_live;
        state_name = BuildingState::NORMAL;
    };
    void setRuin()
    {
        time_to_live = ruin_state_initial_time_to_live;
        state_name = BuildingState::RUIN;
    };
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
};
