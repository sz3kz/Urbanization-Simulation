cmake_minimum_required(VERSION 3.15...4.1)

set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

project(UrbanizationSimulation CXX)

add_compile_options(-Wall -Wextra -pedantic -Werror)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

FetchContent_MakeAvailable(googletest)

add_library(simulation_library
        src/simulation/Simulation.cpp
        src/simulation/Coordinates.cpp
        src/simulation/BoardProbabilities.cpp
        src/simulation/BoardOccupants.cpp
        src/simulation/CellOccupant.cpp
        src/simulation/CellProbabilities.cpp
        src/buildings/House.cpp
        src/buildings/Firestation.cpp
        src/buildings/Shop.cpp
        src/buildings/Factory.cpp
        src/buildings/Church.cpp
)

target_compile_features(simulation_library PUBLIC cxx_std_23)

add_executable(simulation_tests 
  tests/CoordinatesTests.cpp
  tests/BoardTests.cpp
  tests/CellOccupantTests.cpp
)

add_executable(simulation
  src/main.cpp
)

target_include_directories(simulation_library PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(simulation_tests PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_include_directories(simulation PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

target_compile_features(simulation PUBLIC cxx_std_23)
target_compile_features(simulation_tests PUBLIC cxx_std_23)
target_link_libraries(simulation_tests gmock_main gtest gmock simulation_library)
target_link_libraries(simulation simulation_library)

add_custom_target(run_tests
                  COMMAND simulation_tests
                  DEPENDS simulation_tests
                  USES_TERMINAL)

add_custom_target(run_simulation
        COMMAND simulation 50 50 2
        DEPENDS simulation
        USES_TERMINAL)

enable_testing()
add_test(tests simulation_tests)
