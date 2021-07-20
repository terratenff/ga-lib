#pragma once

#include "postgenerationoperator.h"
#include "../population_initializers/tspinitializerrandom.h"

/// <summary>
/// This post-generation operator finds fitness-wise duplicate solutions and replaces
/// them with new (randomly created) solutions.
/// </summary>
class TSPPGODuplicateReplacer : public PostGenerationOperator
{
public:
	TSPPGODuplicateReplacer(ProblemData* data, Evaluator* evaluator, unsigned int generationFrequency, TSPInitializerRandom* initializer);
	void run(RNG* rng, Population* populationNew, Population* populationOld = nullptr) override;
	void print() override;
private:
	TSPInitializerRandom* initializer_;
};

