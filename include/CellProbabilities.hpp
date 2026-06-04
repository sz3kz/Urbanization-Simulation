#pragma once
#include "World.hpp"
#include <map>

namespace EmptyCellDefaultProbabilities
{
inline constexpr double CreateNewHouse{ 0.001 };
inline constexpr double CreateNewFirestation{ 0.00001 };
inline constexpr double CreateNewShop{ 0.00001 };
inline constexpr double CreateNewFactory{ 0.00001 };
inline constexpr double CreateNewChurch{ 0.00001 };
inline constexpr double SetCurrentBuildingOnFire{ 0.0 };
inline constexpr double RestoreBuildingFromRuin{ 0 };
inline constexpr double RestoreBuildingTimeToLive{ 0 };
}

namespace OccupiedCellDefaultProbabilities
{
inline constexpr double CreateNewHouse{ 0.0 };
inline constexpr double CreateNewFirestation{ 0.0 };
inline constexpr double CreateNewShop{ 0.0 };
inline constexpr double CreateNewFactory{ 0.0 };
inline constexpr double CreateNewChurch{ 0.0 };
inline constexpr double SetCurrentBuildingOnFire{ 0.0001 };
inline constexpr double RestoreBuildingFromRuin{ 0 };
inline constexpr double RestoreBuildingTimeToLive{ 0 };
}

enum class CellState : uint8_t
{
    Empty,
    Occupied
};

enum class ProbabilityType : std::uint8_t
{
    CREATE_NEW_HOUSE,
    CREATE_NEW_FIRESTATION,
    CREATE_NEW_SHOP,
    CREATE_NEW_FACTORY,
    CREATE_NEW_CHURCH,
    SET_CURRENT_BUILDING_ON_FIRE,
    RESTORE_TIME_TO_LIVE,
    RESTORE_FROM_RUIN,
};

struct Probability
{
    unsigned long last_updated_at_iteration;
    double value;
};

struct CellProbabilities
{
    std::map<ProbabilityType, Probability> probabilities;
    explicit CellProbabilities(CellState state);
    CellProbabilities()
      : CellProbabilities(CellState::Empty) {};
};