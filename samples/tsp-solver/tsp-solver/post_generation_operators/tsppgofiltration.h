#pragma once

#include "postgenerationoperator.h"
#include "../population_initializers/tspinitializerrandom.h"

/// <summary>
/// This post-generation operator combines two most recent populations into one, keeps the best
/// solutions and replaces duplicates with completely random ones.
/// </summary>
class TSPPGOFiltration : public PostGenerationOperator
{
public:
	TSPPGOFiltration(ProblemData* data, Evaluator* evaluator, unsigned int generationFrequency, TSPInitializerRandom* initializer);
	void run(RNG* rng, Population* populationNew, Population* populationOld = nullptr) override;
	void print() override;
private:
	TSPInitializerRandom* initializer_;
};