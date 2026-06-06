#include "Simulation.hpp"

#include "BoardOccupants.hpp"
#include "Church.hpp"
#include "Coordinates.hpp"
#include "Factory.hpp"
#include "Firestation.hpp"
#include "House.hpp"
#include "Shop.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <memory>
#include <random>
#include <thread>

void Simulation::decayBuildings()
{

    for (unsigned int row_position = 0; row_position < next_board.getWidth(); ++row_position)
        for (unsigned int column_position = 0; column_position < next_board.getHeight();
             ++column_position)
        {
            auto current_coordinates =
              Coordinates(static_cast<int>(row_position), static_cast<int>(column_position));
            /*
            std::cout << "(" << current_coordinates.x << "," << current_coordinates.y << ")
            TIME2LIVE" << '\n';
            */
            bool is_empty = next_board.checkCellEmptyAtCoordinates(current_coordinates);
            if (is_empty)
            {
                /*
                std::cout << "\t EMPTY -> continue" << '\n';
                */
                continue;
            }
            CellOccupant& cell = next_board.getCellAtCoordinates(current_coordinates);
            Building* building = cell.getBuilding();
            if (building->getTimeToLive() < StateConstants::TimeToLiveDecayValue)
            {
                /*
                std::cout << "\t LOW TTL -> STATE TRANSFORMATION" << '\n';
                */
                cell.transformState();
            }
            else
            {
                /*
                std::cout << "\t HIGH TTL -> DECREMENT" << '\n';
                */
                building->decay();
            }
        }
}

void Simulation::incrementIteration()
{
    this->current_iteration++;
}

void Simulation::sleep(std::chrono::milliseconds timespan)
{
    std::this_thread::sleep_for(timespan);
}

void Simulation::recycleBoards()
{
    for (unsigned int i = 0; i < next_board.getWidth(); ++i)
    {
        for (unsigned int j = 0; j < next_board.getHeight(); ++j)
        {
            auto coordinates = Coordinates(static_cast<int>(i), static_cast<int>(j));
            auto next_building = next_board.getCellAtCoordinates(coordinates).release();
            previous_board.acquireOccupantToCoordinates(coordinates, std::move(next_building));
        }
    }
}

void Simulation::executeProbability()
{
    for (unsigned int row_position = 0; row_position < probability_board.getWidth(); ++row_position)
    {
        for (unsigned int column_position = 0; column_position < probability_board.getHeight();
             ++column_position)
        {
            auto current_coordinates =
              Coordinates(static_cast<int>(row_position), static_cast<int>(column_position));
            /* preserve previous value */
            auto previous_occupant =
              previous_board.releaseOccupantAtCoordinates(current_coordinates);
            next_board.acquireOccupantToCoordinates(current_coordinates,
                                                    std::move(previous_occupant));

            auto probabilities =
              probability_board.getCellAtCoordinates(current_coordinates).probabilities;

            bool something_already_built = false;

            for (const auto& [probability_type, probability] : probabilities)
            {
                /* OMG THIS CASE SWITCH DICTATES PROBABILITY PRECEDENSE */
                /* I HAVE TO KEEP TRACK IF AN EMPTY CELL WAS POPULATED WITH A BOOL*/
                /* JESUS CHRIST PLEASE HELP ME */
                const auto& [last_modified_iteration, value] = probability;
                switch (probability_type)
                {
                    case ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE:
                    {
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "SET_BUILDING_ON_FIRE Percentage:" << value << '\n';
                        */

                        if (rollProbabilityDice(value))
                        {
                            /* burn it */
                            next_board.getCellAtCoordinates(current_coordinates)
                              .getBuilding()
                              ->setBuildingState(BuildingState::BURNING);
                        }
                        break;
                    }

                    case ProbabilityType::RESTORE_FROM_RUIN:
                    {
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "RESTORE_FROM_RUIN Percentage:" << value << '\n';
                        */

                        /*
                        std::cout << "Rolling for new ttl restoration..." << '\n';
                        */
                        if (rollProbabilityDice(value))
                        {
                            next_board.getCellAtCoordinates(current_coordinates)
                              .getBuilding()
                              ->setBuildingState(BuildingState::NORMAL);
                        }
                        break;
                    }
                    case ProbabilityType::RESTORE_TIME_TO_LIVE:
                    {
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "RESTORE_TIME_TO_LIVE Percentage:" << value << '\n';
                        */

                        /*
                        std::cout << "Rolling for new ttl restoration..." << '\n';
                        */
                        if (rollProbabilityDice(value))
                        {
                            /* Restore TTL*/
                            /* Need to handle all ttl, although 90% of cases it will be Normal */
                            /* When shop is being burned, it should set the correct TTL, not the
                             * Normal ttl */

                            next_board.getCellAtCoordinates(current_coordinates)
                              .getBuilding()
                              ->resetTimeToLive();
                        }
                        break;
                    }
                    case ProbabilityType::CREATE_NEW_HOUSE:
                    {
                        if (something_already_built)
                        {
                            break;
                        }
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "CREATE_NEW_HOUSE Percentage:" << value << '\n';

                        std::cout << "Rolling for new house..." << '\n';
                        */
                        if (rollProbabilityDice(value))
                        {
                            /* create new House */
                            /*
                            std::cout << "New house!" << '\n';
                            */
                            next_board.acquireOccupantToCoordinates(current_coordinates,
                                                                    std::make_unique<House>());
                            something_already_built = true;
                        }
                        break;
                    }

                    case ProbabilityType::CREATE_NEW_FIRESTATION:
                    {
                        if (something_already_built)
                        {
                            break;
                        }
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "CREATE_NEW_FIRESTATION Percentage:" << value << '\n';
                        */

                        /*
                        std::cout << "Rolling for new firestation..." << '\n';
                        */
                        if (rollProbabilityDice(value))
                        {
                            /* create new Firestation */
                            /*
                            std::cout << "New firestation!" << '\n';
                            */
                            next_board.acquireOccupantToCoordinates(
                              current_coordinates, std::make_unique<Firestation>());
                            something_already_built = true;
                        }
                        break;
                    }

                    case ProbabilityType::CREATE_NEW_SHOP:
                    {
                        if (something_already_built)
                        {
                            break;
                        }
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "CREATE_NEW_SHOP Percentage:" << value << '\n';
                        */

                        /*
                        std::cout << "Rolling for new SHop..." << '\n';
                        */
                        if (rollProbabilityDice(value))
                        {
                            /* create new SHop */
                            /*
                            std::cout << "New Shop!" << '\n';
                            */
                            next_board.acquireOccupantToCoordinates(current_coordinates,
                                                                    std::make_unique<Shop>());
                            something_already_built = true;
                        }
                        break;
                    }

                    case ProbabilityType::CREATE_NEW_FACTORY:
                    {
                        if (something_already_built)
                        {
                            break;
                        }
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "CREATE_NEW_FACTORY Percentage:" << value << '\n';
                        */

                        /*
                        std::cout << "Rolling for new Factory..." << '\n';
                        */
                        if (rollProbabilityDice(value))
                        {
                            /* create new Factory */
                            /*
                            std::cout << "New Factory!" << '\n';
                            */
                            next_board.acquireOccupantToCoordinates(current_coordinates,
                                                                    std::make_unique<Factory>());
                            something_already_built = true;
                        }
                        break;
                    }
                    case ProbabilityType::CREATE_NEW_CHURCH:
                    {
                        if (something_already_built)
                        {
                            break;
                        }
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "CREATE_NEW_CHURCH Percentage:" << value << '\n';
                        */

                        /*
                        std::cout << "Rolling for new CHURCH..." << '\n';
                        */
                        if (rollProbabilityDice(value))
                        {
                            /* create new church */
                            /*
                            std::cout << "New Church!" << '\n';
                            */
                            next_board.acquireOccupantToCoordinates(current_coordinates,
                                                                    std::make_unique<Church>());
                            something_already_built = true;
                        }
                        break;
                    }
                    default:
                        std::cout << "Unrecognized probability type detected!" << '\n';
                }
            }
        }
    }
}

void Simulation::propagateBuildingProbabilities()
{
    for (unsigned int row_position = 0; row_position < previous_board.getWidth(); ++row_position)
    {
        for (unsigned int column_position = 0; column_position < previous_board.getHeight();
             ++column_position)
        {
            auto current_coordinates =
              Coordinates(static_cast<int>(row_position), static_cast<int>(column_position));
            if (previous_board.checkCellEmptyAtCoordinates(current_coordinates))
            {
                continue;
            }
            const auto& cell = previous_board.getCellAtCoordinates(current_coordinates);
            cell.occupant->applyProbabilities(
              [this, row_position, column_position](Coordinates relative_coordinates) -> bool
              {
                  return this->previous_board.checkCellExistsAtCoordinates(
                    Coordinates(static_cast<int>(row_position) + relative_coordinates.x,
                                static_cast<int>(column_position) + relative_coordinates.y));
              },
              [this, row_position, column_position](Coordinates relative_coordinates) -> bool
              {
                  return this->previous_board.checkCellEmptyAtCoordinates(
                    Coordinates(static_cast<int>(row_position) + relative_coordinates.x,
                                static_cast<int>(column_position) + relative_coordinates.y));
              },
              [this, row_position, column_position](Coordinates relative_coordinates,
                                                    ProbabilityType probability_type) -> bool
              {
                  return this->probability_board.checkProbabilityTypePercentageIsSetAtCoordinates(
                    Coordinates(static_cast<int>(row_position) + relative_coordinates.x,
                                static_cast<int>(column_position) + relative_coordinates.y),
                    probability_type,
                    this->current_iteration);
              },
              [this, row_position, column_position](Coordinates relative_coordinates,
                                                    ProbabilityType probability_type) -> double
              {
                  return this->probability_board.getProbabilityTypePercentageAtCoordinates(
                    Coordinates(static_cast<int>(row_position) + relative_coordinates.x,
                                static_cast<int>(column_position) + relative_coordinates.y),
                    probability_type);
              },
              [this, row_position, column_position](Coordinates relative_coordinates,
                                                    ProbabilityType probability_type,
                                                    double percentage) -> void
              {
                  this->probability_board.setProbabilityTypePercentageAtCoordinates(
                    Coordinates(static_cast<int>(row_position) + relative_coordinates.x,
                                static_cast<int>(column_position) + relative_coordinates.y),
                    probability_type,
                    this->current_iteration,
                    percentage);
              },
              [this, row_position, column_position](Coordinates relative_coordinates,
                                                    BuildingState const& state_name) -> bool
              {
                  auto coordinates =
                    Coordinates(static_cast<int>(row_position) + relative_coordinates.x,
                                static_cast<int>(column_position) + relative_coordinates.y);
                  Building const* building =
                    this->previous_board.getCellAtCoordinates(coordinates).getBuilding();
                  return building->getBuildingState() == state_name;
              });
        }
    }
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
    std::ofstream myfile(filename);
    while (true)
    {
        propagateBuildingProbabilities();
        executeProbability();
        decayBuildings();
        recycleBoards();
        probability_board.resetProbabilities(previous_board);
        print(myfile);
        sleep(std::chrono::milliseconds(100));
        incrementIteration();
    }
}

void Simulation::print(std::ofstream& file) const
{
    for (unsigned int _ = 0; _ < 3; ++_)
    {
        std::cout << '\n';
        file << '\n';
    }
    std::cout << previous_board << '\n';
    file << previous_board << '\n';
}
