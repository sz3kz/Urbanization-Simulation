#include "../../include/Simulation.hpp"
#include "../../include/BoardOccupants.hpp"
#include "../../include/Coordinates.hpp"
#include "../../include/House.hpp"
#include "../../include/World.hpp"
#include <chrono>
#include <iostream>
#include <random>
#include <thread>

void Simulation::iterate()
{
    /* 1. iteration: Iterate through previous_board to populate probability_board */
    for (unsigned int row_position = 0; row_position < previous_board.getWidth(); ++row_position)
    {
        for (unsigned int column_position = 0; column_position < previous_board.getHeight();
             ++column_position)
        {
            bool empty = previous_board.checkCellEmptyAtCoordinates(
              Coordinates(row_position, column_position));
            if (empty)
            {
                continue;
            }
            BuildingType building_type =
              previous_board.getCellBuildingType(Coordinates(row_position, column_position));
            if (building_type == BuildingType::HOUSE)
            {
                this->previous_board.contents
                  .at(previous_board.calculateIndexFromCoordinates(
                    Coordinates(row_position, column_position)))
                  .occupant->applyProbabilities(
                    [this, row_position, column_position](Coordinates relative_coordinates)
                    {
                        return this->previous_board.checkCellExistsAtCoordinates(
                          Coordinates(relative_coordinates.x + row_position,
                                      relative_coordinates.y + column_position));
                    },
                    [this, row_position, column_position](Coordinates relative_coordinates)
                    {
                        return this->previous_board.checkCellEmptyAtCoordinates(
                          Coordinates(relative_coordinates.x + row_position,
                                      relative_coordinates.y + column_position));
                    },
                    [this, row_position, column_position](Coordinates relative_coordinates,
                                                          ProbabilityType probability_type)
                    {
                        return this->probability_board
                          .checkProbabilityTypePercentageIsSetAtCoordinates(
                            Coordinates(relative_coordinates.x + row_position,
                                        relative_coordinates.y + column_position),
                            probability_type,
                            this->current_iteration);
                    },
                    [this, row_position, column_position](Coordinates relative_coordinates,
                                                          ProbabilityType probability_type)
                    {
                        return this->probability_board.getProbabilityTypePercentageAtCoordinates(
                          Coordinates(relative_coordinates.x + row_position,
                                      relative_coordinates.y + column_position),
                          probability_type);
                    },
                    [this, row_position, column_position](Coordinates relative_coordinates,
                                                          ProbabilityType probability_type,
                                                          double percentage)
                    {
                        return this->probability_board.setProbabilityTypePercentageAtCoordinates(
                          Coordinates(relative_coordinates.x + row_position,
                                      relative_coordinates.y + column_position),
                          probability_type,
                          this->current_iteration,
                          percentage);
                    });
            }
        }
    }

    /* 2. iteration: Iterate through probability_board to populate next_board */
    for (unsigned int row_position = 0; row_position < probability_board.getWidth(); ++row_position)
    {
        for (unsigned int column_position = 0; column_position < probability_board.getHeight();
             ++column_position)
        {
            auto current_coordinates = Coordinates(row_position, column_position);
            auto probability_type = ProbabilityType::CREATE_NEW_BUILDING;
            double probability_percentage =
              probability_board.getProbabilityTypePercentageAtCoordinates(current_coordinates,
                                                                          probability_type);
            std::cout << "(" << row_position << "," << column_position
                      << "):" << "Percentage:" << probability_percentage << '\n';
            bool probability_success = rollProbabilityDice(probability_percentage);
            if (!probability_success)
            {
                /* preserve previous value */
                auto previous_occupant =
                  previous_board.releaseOccupantAtCoordinates(current_coordinates);
                next_board.acquireOccupantToCoordinates(current_coordinates,
                                                        std::move(previous_occupant));
            }
            else
            {
                /* create new value */
                next_board.acquireOccupantToCoordinates(
                  current_coordinates,
                  std::unique_ptr<House>(new House(default_properties_house_radius)));
            }
        }
    }

    /* 3. Implement time to live */
    for (unsigned int row_position = 0; row_position < next_board.getWidth(); ++row_position)
        for (unsigned int column_position = 0; column_position < next_board.getHeight();
             ++column_position)
        {
            auto current_coordinates = Coordinates(row_position, column_position);
            bool is_empty = next_board.checkCellEmptyAtCoordinates(current_coordinates);
            if (is_empty)
            {
                continue;
            }
            CellOccupant& cell = next_board.getCellACoordinates(current_coordinates);
            Building* building = cell.getBuilding();
            if (building->getTimeToLive() < decay)
            {
                cell.release();
            }
            else
            {
                building->setTimeToLive(building->getTimeToLive() - decay);
            }
        }
    /* 3. Swap boards */
    next_board.contents.swap(previous_board.contents);
    /* 4. Zero out probabilities*/
    probability_board.resetProbabilities();
    this->current_iteration++;
}

auto Simulation::rollProbabilityDice(double percentage) -> bool
{
    std::bernoulli_distribution distribution(percentage);
    bool outcome = distribution(generator);
    return outcome;
}

[[noreturn]]
void Simulation::run()
{
    while (true)
    {
        iterate();
        print();
        std::chrono::seconds timespan(1); // or whatever

        std::this_thread::sleep_for(timespan);
    }
}

void Simulation::print()
{
    std::cout << previous_board << '\n';
}