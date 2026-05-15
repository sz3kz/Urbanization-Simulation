#pragma once

class CellProbabilities {
    public:
        CellProbabilities();
        void recalculateProbabilities();
        void doTurn();
    private:
        int lastModifiedIter;
        float* disasterProbabilities;
        float* buildingProbabilities;
        /*float flammability;
        float robbability;
        float buildingShoppability;
        float buildingHousability;
        float buildingFirestationability;
        float buildingFactorability;
        float buildingChurchability;*/
};
