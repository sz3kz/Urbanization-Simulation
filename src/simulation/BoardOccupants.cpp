#include "../../include/BoardOccupants.hpp"
#include "../../include/Board.hpp"
#include "../../include/Building.hpp"
#include "../../include/Coordinates.hpp"
#include "../../include/House.hpp"
#include "../../include/World.hpp"

auto BoardOccupants::checkCellEmptyAtCoordinates(Coordinates const& coordinates) const -> bool
{
    unsigned int index = calculateIndexFromCoordinates(coordinates);
    return this->contents.at(index).occupant == nullptr;
}

auto BoardOccupants::releaseOccupantAtCoordinates(Coordinates const& coordinates)
  -> std::unique_ptr<Building>
{
    return this->contents.at(calculateIndexFromCoordinates(coordinates)).release();
}

void BoardOccupants::acquireOccupantToCoordinates(Coordinates const& coordinates,
                                                  std::unique_ptr<Building> building)
{
    contents.at(calculateIndexFromCoordinates(coordinates)).occupant = std::move(building);
}

auto BoardOccupants::getCellBuildingType(Coordinates const& coordinates) const -> BuildingType
{
    unsigned int index = calculateIndexFromCoordinates(coordinates);
    return contents.at(index).occupant->getBuildingType();
}

auto operator<<(std::ostream& os, BoardOccupants const& board) -> std::ostream&
{
    for (unsigned int i = 0; i < board.getWidth(); ++i)
    {
        for (unsigned int j = 0; j < board.getHeight(); ++j)
        {
            auto current_coordinates = Coordinates(static_cast<int>(i), static_cast<int>(j));
            os << board.contents.at(board.calculateIndexFromCoordinates(current_coordinates));
        }
        os << '\n';
    }
    return os;
}