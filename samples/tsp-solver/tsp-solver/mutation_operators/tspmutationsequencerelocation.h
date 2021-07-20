#pragma once

#include "mutationoperator.h"

/// <summary>
/// Selects a gene within a chromosome at random and moves it elsewhere in the same chromosome.
/// This is attempted a fixed number of times. If resulting fitness value is better than
/// what is was initially, the mutation process is terminated sooner.
/// </summary>
class TSPMutationSequenceRelocation : public MutationOperator
{
public:
	TSPMutationSequenceRelocation(ProblemData* data, Evaluator* evaluator, unsigned int useWeight, unsigned int attemptCount = 1, unsigned int resetCount = 10);
	void run(Solution* offspring, RNG* rng) override;
	void print() override;
private:
	unsigned int attemptCount_;
	unsigned int resetCount_;
};

