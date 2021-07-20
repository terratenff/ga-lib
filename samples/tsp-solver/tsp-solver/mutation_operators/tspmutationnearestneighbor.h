#pragma once

#include "mutationoperator.h"

/// <summary>
/// Mutation operator that utilizes the nearest neighbor heuristic to optimize
/// solutions to the TSP. A gene within a chromosome is selected at random, which
/// is then subjected to the heuristic.
/// </summary>
class TSPMutationNearestNeighbor : public MutationOperator
{
public:
	TSPMutationNearestNeighbor(ProblemData* data, Evaluator* evaluator, unsigned int useWeight);
	void run(Solution* offspring, RNG* rng) override;
	void print() override;
};
