#pragma once

#include "crossoveroperator.h"

/// <summary>
/// One point crossover operator. One point is selected at random. Elements after that are swapped
/// between the chromosomes. The rest of the elements are adjusted so that there are no
/// duplicate/missing elements.
/// </summary>
class TSPCrossoverOnePoint : public CrossoverOperator
{
public:
	TSPCrossoverOnePoint(ProblemData* data, Evaluator* evaluator, unsigned int useWeight);
	std::pair<Solution*, Solution*> run(Solution* parent1, Solution* parent2, RNG* rng) override;
	void print() override;
};

