#pragma once

#include "mutationoperator.h"

/// <summary>
/// Selects two elements within a chromosome at random and swaps their positions.
/// This is attempted a fixed number of times. If resulting fitness value is better than
/// what it was initially, the mutation process is terminated sooner. Poorly performing
/// element swaps are undone (except for the final attempt).
/// </summary>
class TSPMutationSwap : public MutationOperator
{
public:
	TSPMutationSwap(ProblemData* data, Evaluator* evaluator, unsigned int useWeight, unsigned int attemptCount = 1);
	void run(Solution* offspring, RNG* rng) override;
	void print() override;
private:
	unsigned int attemptCount_;
};
