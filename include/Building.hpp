#pragma once

class Building
{
public:
    virtual ~Building() = default;

    Building(const Building&) = delete;
    auto operator=(const Building&) -> Building& = delete;

    Building(Building&&) = default;
    auto operator=(Building&&) -> Building& = default;

    void setOnFire();
    void extinguishFire();
    void decayToRuin();
    void restoreRuin();
    
    virtual void applyProbabilities();

    void doTurn();

protected:
    // Constructor (protected if you don't want direct instantiation of 'Building')
    Building() = default;
};
