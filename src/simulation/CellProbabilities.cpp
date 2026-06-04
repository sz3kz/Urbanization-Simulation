#include "CellProbabilities.hpp"

#include <stdexcept>

CellProbabilities::CellProbabilities(CellState state)
{
    switch (state)
    {
        case CellState::Empty:
            probabilities[ProbabilityType::CREATE_NEW_HOUSE] =
              Probability(0, EmptyCellDefaultProbabilities::CreateNewHouse);
            probabilities[ProbabilityType::CREATE_NEW_CHURCH] =
              Probability(0, EmptyCellDefaultProbabilities::CreateNewChurch);
            probabilities[ProbabilityType::CREATE_NEW_SHOP] =
              Probability(0, EmptyCellDefaultProbabilities::CreateNewShop);
            probabilities[ProbabilityType::CREATE_NEW_FACTORY] =
              Probability(0, EmptyCellDefaultProbabilities::CreateNewFactory);
            probabilities[ProbabilityType::CREATE_NEW_FIRESTATION] =
              Probability(0, EmptyCellDefaultProbabilities::CreateNewFirestation);
            probabilities[ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE] =
              Probability(0, EmptyCellDefaultProbabilities::SetCurrentBuildingOnFire);
            probabilities[ProbabilityType::RESTORE_FROM_RUIN] =
              Probability(0, EmptyCellDefaultProbabilities::RestoreBuildingFromRuin);
            probabilities[ProbabilityType::RESTORE_TIME_TO_LIVE] =
              Probability(0, EmptyCellDefaultProbabilities::RestoreBuildingTimeToLive);
            break;
        case CellState::Occupied:
            probabilities[ProbabilityType::CREATE_NEW_HOUSE] =
              Probability(0, OccupiedCellDefaultProbabilities::CreateNewHouse);
            probabilities[ProbabilityType::CREATE_NEW_CHURCH] =
              Probability(0, OccupiedCellDefaultProbabilities::CreateNewChurch);
            probabilities[ProbabilityType::CREATE_NEW_SHOP] =
              Probability(0, OccupiedCellDefaultProbabilities::CreateNewShop);
            probabilities[ProbabilityType::CREATE_NEW_FACTORY] =
              Probability(0, OccupiedCellDefaultProbabilities::CreateNewFactory);
            probabilities[ProbabilityType::CREATE_NEW_FIRESTATION] =
              Probability(0, OccupiedCellDefaultProbabilities::CreateNewFirestation);
            probabilities[ProbabilityType::SET_CURRENT_BUILDING_ON_FIRE] =
              Probability(0, OccupiedCellDefaultProbabilities::SetCurrentBuildingOnFire);
            probabilities[ProbabilityType::RESTORE_FROM_RUIN] =
              Probability(0, OccupiedCellDefaultProbabilities::RestoreBuildingFromRuin);
            probabilities[ProbabilityType::RESTORE_TIME_TO_LIVE] =
              Probability(0, OccupiedCellDefaultProbabilities::RestoreBuildingTimeToLive);
            break;
        default:
            throw std::invalid_argument("Unknown cell state");
    }
}