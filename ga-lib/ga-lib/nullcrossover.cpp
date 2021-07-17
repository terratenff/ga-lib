#include "pch.h"
#include "nullcrossover.h"
#include <iostream>
#include <string>

NullCrossover::NullCrossover(ProblemData* data, Evaluator* evaluator, unsigned int useWeight):
	CrossoverOperator(data, evaluator, useWeight)
{
}

std::pair<Solution*, Solution*> NullCrossover::run(Solution* parent1, Solution* parent2, RNG* rng)
{
	Solution* offspring1 = parent1->clone();
	Solution* offspring2 = parent2->clone();
	std::pair<Solution*, Solution*> pair;
	pair.first = offspring1;
	pair.second = offspring2;
	return pair;
}

void NullCrossover::print()
{
	std::string text = "No Crossover (Weight: " + std::to_string(getUseWeight()) + ")";
	std::cout << text << std::endl;
}
