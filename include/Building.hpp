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
namespace BuildingRadius
{
inline constexpr unsigned int house_radius = 2;
inline constexpr unsigned int shop_radius = 4;
inline constexpr unsigned int firestation_radius = 6;
inline constexpr unsigned int factory_radius = 4;
inline constexpr unsigned int church_radius = 4;
}

class Building
{
  protected:
    std::string emoji{ "❌" };
    unsigned int radius{ 0 };
    std::unique_ptr<State> building_state;

    void setRadius(const unsigned int new_radius) { radius = new_radius; }

  public:
    Building()
      : building_state(std::make_unique<State>()) {};
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
    auto getRadius() const -> unsigned int;

    [[nodiscard]]
    auto getBuildingState() const -> BuildingState;

    void setBuildingState(BuildingState const& supplied_building_state) const;

    [[nodiscard]]
    auto getTimeToLive() const -> unsigned int;

    void decay() const;

    void resetTimeToLive() const;

    void setEmoji(std::string const& supplied_emoji);

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
