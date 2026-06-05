#pragma once
#include <cstdint>
enum class ArgumentType : std::uint8_t
{
    EXEC_NAME,
    WIDTH,
    HEIGHT,
    SEED,
    OUTPUT_FILENAME,
    ARGS,
};