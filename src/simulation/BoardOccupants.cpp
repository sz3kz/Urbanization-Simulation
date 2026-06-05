#include "../../include/BoardOccupants.hpp"
#include "../../include/Board.hpp"
#include "../../include/Building.hpp"
#include "../../include/Coordinates.hpp"

auto BoardOccupants::checkCellEmptyAtCoordinates(Coordinates const& coordinates) const -> bool
{
    const auto& cell = this->getCellAtCoordinates(coordinates);
    return cell.occupant == nullptr;
}

auto BoardOccupants::releaseOccupantAtCoordinates(Coordinates const& coordinates)
  -> std::unique_ptr<Building>
{
    auto& cell = this->getCellAtCoordinates(coordinates);
    return cell.release();
}

void BoardOccupants::acquireOccupantToCoordinates(Coordinates const& coordinates,
                                                  std::unique_ptr<Building> building)
{
    auto& cell = this->getCellAtCoordinates(coordinates);
    cell.occupant = std::move(building);
}

auto BoardOccupants::getCellBuildingType(Coordinates const& coordinates) const -> BuildingType
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
    auto const& cell = this->getCellAtCoordinates(coordinates);
    return cell.occupant->getBuildingType();
}

auto operator<<(std::ostream& os, BoardOccupants const& board) -> std::ostream&
{
    for (unsigned int i = 0; i < board.getWidth(); ++i)
    {
        for (unsigned int j = 0; j < board.getHeight(); ++j)
        {
            os << board.getCellAtCoordinates(Coordinates(static_cast<int>(i), static_cast<int>(j)));
        }
        os << '\n';
    }
    return os;
}