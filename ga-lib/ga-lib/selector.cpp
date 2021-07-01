#include "pch.h"
#include "selector.h"

Selector::Selector(unsigned int candidateCount, unsigned int useWeight):
    candidateCount_(candidateCount),
    useWeight_(useWeight)
{
}

unsigned int Selector::getUseWeight()
{
    return useWeight_;
}
