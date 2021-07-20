#pragma once

#include "postgenerationoperator.h"

/// <summary>
/// This post-generation operator retains random solutions from the previous population
/// in order to maintain some form of population diversity. They replace solutions at random.
/// </summary>
class TSPPGORetention : public PostGenerationOperator
{
public:
	TSPPGORetention(ProblemData* data, Evaluator* evaluator, unsigned int generationFrequency, float retentionRate = 0.10f);
	void run(RNG* rng, Population* populationNew, Population* populationOld = nullptr) override;
	void print() override;
private:
	float retentionRate_;
};
