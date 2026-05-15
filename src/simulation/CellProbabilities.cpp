#include "CellProbabilities.hpp"
#include "World.hpp"

CellProbabilities::CellProbabilities()
{
    lastModifiedIter = -1;
    buildingProbabilities = new float[NUM_BUILDINGTYPES];
    for (int i =0;i<(int) NUM_BUILDINGTYPES;i++)
    {
        //TODO przydalby sie jakis sposob wstawienia wartosci domyslnych
    }

    disasterProbabilities = new float[NUM_DISASTERTYPES];
    for (int i =0;i<(int) NUM_BUILDINGTYPES;i++)
    {
        //TODO przydalby sie jakis sposob wstawienia wartosci domyslnych
    }
}