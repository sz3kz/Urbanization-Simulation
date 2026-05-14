# Urbanization-Simulation
## Installation
First, download the repository.
```bash
git clone git@github.com:sz3kz/Urbanization-Simulation.git
cd Urbanization-Simulation/
```
Then, set up the environment and run (only tests for now):
```bash
make check-prerequesites
cmake -S . -B ninja -G Ninja 
cd build/
ninja run_tests
```
**BONUS**: Setup can also be done entirely via the makefile:
```bash
make init   # also installs pre-commit hooks
make test
```
