cmake_minimum_required(VERSION 3.12)

project(UrbanizationSimulation CXX)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_options(-Wall -Wextra -pedantic -Werror)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

FetchContent_MakeAvailable(googletest)

add_library(simulation
  src/simulation/Simulation.cpp
  src/simulation/Board.cpp
  src/simulation/CellOccupant.cpp
  src/simulation/CellProbabilities.cpp
  src/simulation/Coordinates.cpp
  src/buildings/Building.cpp
  src/buildings/Church.cpp
  src/buildings/Factory.cpp
  src/buildings/Firestation.cpp
  src/buildings/House.cpp
  src/buildings/Shop.cpp
  src/randomEvents/Disaster.cpp
  src/randomEvents/Fire.cpp
  src/randomEvents/RandomEvent.cpp
  src/randomEvents/Robbery.cpp
  src/randomEvents/Tornado.cpp
)
target_include_directories(simulation PUBLIC include)
target_compile_features(simulation PUBLIC cxx_std_23)

add_executable(simulation_tests 
  tests/BoardTests.cpp
  tests/BuildingTests.cpp
  tests/CellOccupantTests.cpp
  tests/CellProbabilitiesTests.cpp
  tests/CoordinatesTests.cpp
  tests/FactoryTests.cpp
  tests/FirestationTests.cpp
  tests/HouseTests.cpp
  tests/ShopTests.cpp
  tests/SimulationTests.cpp
  tests/ExampleTests.cpp
)
target_include_directories(simulation_tests PUBLIC include)
target_compile_features(simulation_tests PUBLIC cxx_std_23)
target_link_libraries(simulation_tests gmock_main gtest gmock simulation)

add_custom_target(run_tests
                  COMMAND simulation_tests
                  DEPENDS simulation_tests
                  USES_TERMINAL)

enable_testing()
add_test(tests simulation_tests)

