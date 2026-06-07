# Urbanization-Simulation

## Team
* Jan Kranz (Leader)
* Adam Miękisiak

## Goal
The goal was to practice OOP concepts by creating a program simulating 
the process of urban growth and evolution. A 2-dimensional grid is 
created which cells represent a strip of land, empty or occupied by 
buildings. Each building type plays its unique role in the overall urban 
progress via their custom algorithm.

The project heavily utilizes probability computation, which is used as a 
model simply describing complex human behavior.

## Technical Details
All diagrams are inside the `meta/` directory.

## Usage
### User
These are the minimum prerequesites to running the simulation:
* make
* ninja
* cmake
* g++ gnu compiler
* doxygen 
* graphviz (dot)
First, download the repository:
```bash
git clone git@github.com:sz3kz/Urbanization-Simulation.git
cd Urbanization-Simulation/
```
Then, set up the environment:
```bash
cmake -S . -B build -G Ninja 
```
**BONUS**: You can generate documentation for the project:
```bash
doxygen Doxyfile
```
Lastly, decide whether to run tests or execute the simulation:
```bash
cd build/
````
```bash
ninja simulation_tests && ./simulation_tests
```
```bash
ninja simulation && ./simulation <width> <height> <random_seed_value> <output_file_name>
```
<video src="meta/demo.mp4" width="100%" controls></video>

### Developer 
These are the minimum prerequesites to running the simulation:
* make 
* ninja 
* cmake 
* pre-commit 
* g++ 
* clang-format 
* clang-tidy 
* cppcheck 
* graphviz (dot)
First, download the repository.
```bash
git clone git@github.com:sz3kz/Urbanization-Simulation.git
cd Urbanization-Simulation/
```
Then, set up the environment:
```bash
make check-prerequesites
pre-commit install
pre-commit install --hook-type pre-push
cmake -S . -B build -G Ninja 
```
Lastly, decide whether to run tests or execute the simulation:
```bash
cd build/
```
```bash
ninja simulation_tests && ./simulation_tests
ninja run_tests
```
```bash
ninja simulation && ./simulation <width> <height> <random_seed_value> <output_file_name>
ninja run_simulation
```
**BONUS**: Setup can also be done entirely via the makefile:
```bash
make check-prerequesites
make init
make test
make run 
```
