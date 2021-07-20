#pragma once

#include "crossoveroperator.h"

/// <summary>
/// Order crossover operator. A gene within chromosome 1 is selected at random.
/// It is then preserved content-wise and location-wise in chromosome 2.
/// </summary>
class TSPCrossoverOrder: public CrossoverOperator
{
public:
	TSPCrossoverOrder(ProblemData* data, Evaluator* evaluator, unsigned int useWeight);
	std::pair<Solution*, Solution*> run(Solution* parent1, Solution* parent2, RNG* rng) override;
	void print() override;
};

