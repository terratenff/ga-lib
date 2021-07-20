#include "tspselectorroulettewheel.h"
#include <numeric>
#include <iostream>
#include <string>

TSPSelectorRouletteWheel::TSPSelectorRouletteWheel(unsigned int candidateCount, unsigned int useWeight):
	Selector(candidateCount, useWeight)
{
}

Solution* TSPSelectorRouletteWheel::select(Population* population, RNG* rng)
{
	std::vector<unsigned int> indices(population->size());
	std::iota(indices.begin(), indices.end(), 0);
	std::random_shuffle(indices.begin(), indices.end());
	std::vector<Solution*> candidatePool = {};

	float totalFitness = 0;
	for (unsigned int i = 0; i < candidateCount_; i++)
	{
		Solution* solution = population->getSolution(indices[i]);
		float fitness = solution->getFitness();
		float penalty = solution->getPenalty();
		candidatePool.push_back(solution);
		totalFitness += fitness - penalty;
	}
	float randomNumber = float(rng->rand()) / float(RAND_MAX);
	float cumulativeProbability = 0.0f;
	for (Solution* solution : candidatePool)
	{
		cumulativeProbability += float(1 - (solution->getFitness() - solution->getPenalty()) / totalFitness);
		if (randomNumber < cumulativeProbability) return solution;
	}
	return candidatePool[0];
}

void TSPSelectorRouletteWheel::print()
{
	std::string text = "Roulette Wheel Selection (Weight: " + std::to_string(getUseWeight()) + ")";
	std::cout << text << std::endl;
}
