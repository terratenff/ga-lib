#pragma once

#include "selector.h"

/// <summary>
/// Selects a parent from a pool of candidates based on the tournament method.
/// Solution candidates are sorted by their fitness values (penalty values included).
/// Then probabilities of candidates winning are calculated from given base probability
/// (1st place candidate win probability).
/// </summary>
class TSPSelectorTournament: public Selector
{
public:
	TSPSelectorTournament(unsigned int candidateCount, unsigned int useWeight, double baseProbability = 0.80);
	Solution* select(Population* population, RNG* rng) override;
	void print() override;
private:
	double baseProbability_ = 0.80;
};

