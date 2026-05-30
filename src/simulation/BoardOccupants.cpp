#include "../../include/BoardOccupants.hpp"
#include "../../include/Board.hpp"
#include "../../include/Building.hpp"
#include "../../include/Coordinates.hpp"
#include "../../include/House.hpp"
#include "../../include/World.hpp"

auto BoardOccupants::checkCellEmptyAtCoordinates(Coordinates const& coordinates) -> bool
{
    unsigned int index = calculateIndexFromCoordinates(coordinates);
    if (this->contents.at(index).occupant == nullptr)
    {
        return true;
    }
    return false;
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

auto BoardOccupants::getCellBuildingType(Coordinates const& coordinates) -> BuildingType
{
    /*
    unsigned int index = calculateIndexFromCoordinates(coordinates);
    House * is_house = dynamic_cast<House*>(contents.at(index).occupant.get());
    if (is_house)
    {
        std::cout << "House Building Type found!" << std::endl;
        return BuildingType::HOUSE;
    }
    return BuildingType::NONE;
    */
    unsigned int index = calculateIndexFromCoordinates(coordinates);
    return contents.at(index).occupant->getBuildingType();
}

auto operator<<(std::ostream& os, BoardOccupants const& board) -> std::ostream&
{
    for (unsigned int i = 0; i < board.getWidth(); ++i)
    {
        for (unsigned int j = 0; j < board.getHeight(); ++j)
        {
            os << board.contents.at(board.calculateIndexFromCoordinates(Coordinates(i, j)));
        }
        os << '\n';
    }
    return os;
}