#include "tspselectortournament.h"
#include <numeric>
#include <algorithm>
#include <iostream>
#include <string>

TSPSelectorTournament::TSPSelectorTournament(unsigned int candidateCount, unsigned int useWeight, double baseProbability):
	Selector(candidateCount, useWeight), baseProbability_(baseProbability)
{
}

Solution* TSPSelectorTournament::select(Population* population, RNG* rng)
{
	std::vector<unsigned int> indices(population->size());
	std::iota(indices.begin(), indices.end(), 0);
	std::random_shuffle(indices.begin(), indices.end());
	std::vector<Solution*> candidatePool = {};
	for (unsigned int i = 0; i < candidateCount_; i++)
	{
		candidatePool.push_back(population->getSolution(indices[i]));
	}
	std::sort(candidatePool.begin(), candidatePool.end(), [](Solution* lhs, Solution* rhs) {
		return *lhs < *rhs;
	});
	double probability = baseProbability_;
	float randomNumber = float(rng->rand()) / float(RAND_MAX);
	for (unsigned int i = 0; i < candidatePool.size(); i++)
	{
		if (randomNumber < probability)
		{
			return candidatePool[i];
		}
		else
		{
			probability += baseProbability_ * pow(1 - baseProbability_, i + 1);
		}
	}
	return candidatePool[candidatePool.size() - 1];
}

void TSPSelectorTournament::print()
{
	std::string text = "Tournament Selection (Weight: " + std::to_string(getUseWeight()) + ", Win Probability: " + std::to_string(baseProbability_) + ")";
	std::cout << text << std::endl;
}
