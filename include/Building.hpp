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
  protected:
    unsigned int radius;
    unsigned int time_to_live;
    std::string state_name;
    Building(unsigned int radius)
      : radius(radius)
    {
        this->setNormal();
    };

  public:
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
    auto getStateName() const -> std::string
    {
        return this->state_name;
    };
    void setBurning()
    {
        time_to_live = burning_state_initial_time_to_live;
        state_name = "Burning";
    };
    void setNormal()
    {
        time_to_live = normal_state_initial_time_to_live;
        state_name = "Normal";
    };
    void setRuin()
    {
        time_to_live = ruin_state_initial_time_to_live;
        state_name = "Ruin";
    };
    // Function that populates probability_board with probabilities
    virtual void applyProbabilities(
      std::function<bool(Coordinates)> askCellExistsAtCoordinates,
      std::function<bool(Coordinates)> askCellEmptyAtCoordinates,
      std::function<bool(Coordinates, ProbabilityType)>
        askProbabilityTypePercentageIsSetAtCoordinates,
      std::function<double(Coordinates, ProbabilityType)> getProbabilityTypePercentageAtCoordinates,
      std::function<void(Coordinates, ProbabilityType, double)>
        setProbabilityTypePercentageAtCoordinates) = 0;
};