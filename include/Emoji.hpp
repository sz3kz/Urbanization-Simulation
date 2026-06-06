#pragma once
#include <string>

/**
 * @brief Unicode emoji representations used when rendering the simulation.
 *
 * This namespace contains the visual symbols used to display buildings,
 * terrain, and building states on the board.
 */
namespace Emoji
{
/**
 * @brief Emoji representing a house.
 */
inline constexpr std::string House{ "🏠" };

/**
 * @brief Emoji representing a shop.
 */
inline constexpr std::string Shop{ "🏪" };

/**
 * @brief Emoji representing a church.
 */
inline constexpr std::string Church{ "⛪" };

/**
 * @brief Emoji representing a factory.
 */
inline constexpr std::string Factory{ "🏭" };

/**
 * @brief Emoji representing a fire station (there is no firestation emoji so a fire truck must do).
 */
inline constexpr std::string FireTruck{ "🚒" };

/**
 * @brief Emoji displayed for buildings currently on fire.
 */
inline constexpr std::string Fire{ "🔥️" };

/**
 * @brief Emoji displayed for ruined buildings.
 */
inline constexpr std::string DerelictHouse{ "🏚️" };

/**
 * @brief Emoji displayed for empty board cells.
 */
inline constexpr std::string BlueTile{ "🟦️" };
}