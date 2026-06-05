#pragma once
#include <cstdint>
#include <string>

enum class BuildingType : std::uint8_t
{
    SHOP,
    HOUSE,
    FIRESTATION,
    FACTORY,
    CHURCH,
};

namespace Emoji
{
inline constexpr std::string House{ "🏠" };
inline constexpr std::string Shop{ "🏪" };
inline constexpr std::string Church{ "⛪" };
inline constexpr std::string Factory{ "🏭" };
inline constexpr std::string FireTruck{ "🚒" };
inline constexpr std::string Fire{ "🔥️" };
inline constexpr std::string DerelictHouse{ "🏚️" };
inline constexpr std::string BlueTile{ "🟦️" };
}