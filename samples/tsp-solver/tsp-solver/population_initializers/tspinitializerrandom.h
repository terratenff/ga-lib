#pragma once

#include "populationinitializer.h"
#include "../tspsolution.h"
#include "../tspdata.h"

/// <summary>
/// Creates solutions to the TSP completely randomly.
/// </summary>
class TSPInitializerRandom : public PopulationInitializer
{
public:
	TSPInitializerRandom(ProblemData* data, Evaluator* evaluator, unsigned int useWeight);
	Population* createPopulation(unsigned int populationSize) override;
	Solution* createSolution() override;
	void print() override;
};

