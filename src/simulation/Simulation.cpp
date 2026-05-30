#include "../../include/Simulation.hpp"

#include "../../include/BoardOccupants.hpp"
#include "../../include/Coordinates.hpp"
#include "../../include/Firestation.hpp"
#include "../../include/House.hpp"
#include "../../include/Shop.hpp"
#include "../../include/World.hpp"
#include "Church.hpp"
#include "Factory.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>

void Simulation::setEmptyCellBurningProbabilityToZero()
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
                probability_board.setProbabilityTypePercentageAtCoordinates(
                  current_coordinates,
                  ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE,
                  current_iteration,
                  0.0);
            }
        }
    }
}

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
            if (building->getTimeToLive() < decay)
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
                building->setTimeToLive(building->getTimeToLive() - decay);
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
    this->next_board.contents.swap(this->previous_board.contents);
}

void Simulation::executeProbability()
{
    for (unsigned int row_position = 0; row_position < probability_board.getWidth(); ++row_position)
    {
        for (unsigned int column_position = 0; column_position < probability_board.getHeight();
             ++column_position)
        {
            auto current_coordinates = Coordinates(row_position, column_position);
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
                auto& [last_modified_iteration, value] = probability;
                switch (probability_type)
                {
                    case (ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE):
                    {
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "SET_BUILDING_ON_FIRE Percentage:" << value << '\n';
                        */
                        bool probability_success = rollProbabilityDice(value);

                        if (probability_success)
                        {
                            /* burn it */
                            next_board.getCellAtCoordinates(current_coordinates)
                              .getBuilding()
                              ->setBurning();
                        }
                        break;
                    }

                    case (ProbabilityType::RESTORE_FROM_RUIN):
                    {
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "RESTORE_FROM_RUIN Percentage:" << value << '\n';
                        */
                        bool probability_success = rollProbabilityDice(value);

                        /*
                        std::cout << "Rolling for new ttl restoration..." << '\n';
                        */
                        if (probability_success)
                        {
                            next_board.getCellAtCoordinates(current_coordinates)
                              .getBuilding()
                              ->setNormal();
                        }
                        break;
                    }
                    case (ProbabilityType::RESTORE_TIME_TO_LIVE):
                    {
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "RESTORE_TIME_TO_LIVE Percentage:" << value << '\n';
                        */
                        bool probability_success = rollProbabilityDice(value);

                        /*
                        std::cout << "Rolling for new ttl restoration..." << '\n';
                        */
                        if (probability_success)
                        {
                            /* Restore TTL*/
                            /* Need to handle all ttl, although 90% of cases it will be normal */
                            /* When shop is being burned, it should set the correct TTL, not the
                             * normal ttl */
                            if (next_board.getCellAtCoordinates(current_coordinates)
                                  .getBuilding()
                                  ->getStateName() == "Normal")
                            {
                                /* Primary use case */
                                next_board.getCellAtCoordinates(current_coordinates)
                                  .getBuilding()
                                  ->setTimeToLive(normal_state_initial_time_to_live);
                            }
                            else if (next_board.getCellAtCoordinates(current_coordinates)
                                       .getBuilding()
                                       ->getStateName() == "Burning")
                            {
                                /* Should only proc for shops which were burned in current iteration
                                 */
                                /* Maybe proc for Houses in the same situation too... but during
                                 * testing the problem was not observable */
                                next_board.getCellAtCoordinates(current_coordinates)
                                  .getBuilding()
                                  ->setTimeToLive(burning_state_initial_time_to_live);
                            }
                            else if (next_board.getCellAtCoordinates(current_coordinates)
                                       .getBuilding()
                                       ->getStateName() == "Ruin")
                            {
                                /* Should only proc for shops which were ruined in current
                                 * iteration... but during testing the problem was not observable */
                                next_board.getCellAtCoordinates(current_coordinates)
                                  .getBuilding()
                                  ->setTimeToLive(ruin_state_initial_time_to_live);
                            }
                        }
                        break;
                    }
                    case (ProbabilityType::CREATE_NEW_HOUSE):
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
                        bool probability_success = rollProbabilityDice(value);
                        if (probability_success)
                        {
                            /* create new House */
                            /*
                            std::cout << "New house!" << '\n';
                            */
                            next_board.acquireOccupantToCoordinates(
                              current_coordinates,
                              std::unique_ptr<House>(new House(default_properties_house_radius)));
                            something_already_built = true;
                        }
                        break;
                    }

                    case (ProbabilityType::CREATE_NEW_FIRESTATION):
                    {
                        if (something_already_built)
                        {
                            break;
                        }
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "CREATE_NEW_FIRESTATION Percentage:" << value << '\n';
                        */
                        bool probability_success = rollProbabilityDice(value);

                        /*
                        std::cout << "Rolling for new firestation..." << '\n';
                        */
                        if (probability_success)
                        {
                            /* create new Firestation */
                            /*
                            std::cout << "New firestation!" << '\n';
                            */
                            next_board.acquireOccupantToCoordinates(
                              current_coordinates,
                              std::unique_ptr<Firestation>(
                                new Firestation(default_properties_firestation_radius)));
                            something_already_built = true;
                        }
                        break;
                    }

                    case (ProbabilityType::CREATE_NEW_SHOP):
                    {
                        if (something_already_built)
                        {
                            break;
                        }
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "CREATE_NEW_SHOP Percentage:" << value << '\n';
                        */
                        bool probability_success = rollProbabilityDice(value);

                        /*
                        std::cout << "Rolling for new SHop..." << '\n';
                        */
                        if (probability_success)
                        {
                            /* create new SHop */
                            /*
                            std::cout << "New Shop!" << '\n';
                            */
                            next_board.acquireOccupantToCoordinates(
                              current_coordinates,
                              std::unique_ptr<Shop>(new Shop(default_properties_shop_radius)));
                            something_already_built = true;
                        }
                        break;
                    }

                    case (ProbabilityType::CREATE_NEW_FACTORY):
                    {
                        if (something_already_built)
                        {
                            break;
                        }
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "CREATE_NEW_FACTORY Percentage:" << value << '\n';
                        */
                        bool probability_success = rollProbabilityDice(value);

                        /*
                        std::cout << "Rolling for new Factory..." << '\n';
                        */
                        if (probability_success)
                        {
                            /* create new Factory */
                            /*
                            std::cout << "New Factory!" << '\n';
                            */
                            next_board.acquireOccupantToCoordinates(
                              current_coordinates,
                              std::unique_ptr<Factory>(
                                new Factory(default_properties_factory_radius)));
                            something_already_built = true;
                        }
                        break;
                    }
                    case (ProbabilityType::CREATE_NEW_CHURCH):
                    {
                        if (something_already_built)
                        {
                            break;
                        }
                        /*
                        std::cout << "(" << row_position << "," << column_position
                                  << "):" << "CREATE_NEW_CHURCH Percentage:" << value << '\n';
                        */
                        bool probability_success = rollProbabilityDice(value);

                        /*
                        std::cout << "Rolling for new CHURCH..." << '\n';
                        */
                        if (probability_success)
                        {
                            /* create new church */
                            /*
                            std::cout << "New Church!" << '\n';
                            */
                            next_board.acquireOccupantToCoordinates(
                              current_coordinates,
                              std::unique_ptr<Church>(
                                new Church(default_properties_church_radius)));
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
            this->previous_board.contents
              .at(previous_board.calculateIndexFromCoordinates(current_coordinates))
              .occupant->applyProbabilities(
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
                                                      std::string const& state_name) -> bool
                {
                    auto coordinates =
                      Coordinates(static_cast<int>(row_position) + relative_coordinates.x,
                                  static_cast<int>(column_position) + relative_coordinates.y);
                    Building const* building =
                      this->previous_board.getCellAtCoordinates(coordinates).getBuilding();
                    return building->getStateName() == state_name;
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
    std::ofstream myfile("output.txt");
    while (true)
    {
        setEmptyCellBurningProbabilityToZero();
        propagateBuildingProbabilities();
        executeProbability();
        decayBuildings();
        recycleBoards();
        probability_board.resetProbabilities();
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
