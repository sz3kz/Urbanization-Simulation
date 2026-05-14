cmake_minimum_required(VERSION 3.15...4.1)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(UrbanizationSimulation CXX)

add_compile_options(-Wall -Wextra -pedantic -Werror)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

FetchContent_MakeAvailable(googletest)

add_library(simulation
        src/simulation/Coordinates.cpp
)
target_include_directories(simulation PUBLIC include)
target_compile_features(simulation PUBLIC cxx_std_23)

add_executable(simulation_tests 
  tests/CoordinatesTests.cpp
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