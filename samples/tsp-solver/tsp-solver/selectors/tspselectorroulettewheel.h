#pragma once

#include "selector.h"

/// <summary>
/// Selects a parent from a pool of candidates based on the roulette wheel method.
/// Solution fitness divided by total fitness among candidates equals solution's
/// probability of being chosen. Existing penalty values reduce the probability
/// of being chosen.
/// </summary>
class TSPSelectorRouletteWheel: public Selector
{
public:
	TSPSelectorRouletteWheel(unsigned int candidateCount, unsigned int useWeight);
	Solution* select(Population* population, RNG* rng) override;
	void print() override;
};

