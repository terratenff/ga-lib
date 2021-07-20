#pragma once

#include "postgenerationoperator.h"

/// <summary>
/// This post-generation operator adds random generation-best solutions into the new population
/// in order to maintain some form of elitism in the population. They replace solutions that
/// perform poorly in terms of fitness.
/// </summary>
class TSPPGOElitism : public PostGenerationOperator
{
public:
	TSPPGOElitism(ProblemData* data, Evaluator* evaluator, unsigned int generationFrequency, float retentionRate = 0.10f);
	void run(RNG* rng, Population* populationNew, Population* populationOld = nullptr) override;
	void print() override;
private:
	float retentionRate_;
};