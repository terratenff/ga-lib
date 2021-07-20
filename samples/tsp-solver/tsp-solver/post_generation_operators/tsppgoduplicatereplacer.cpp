#include "tsppgoduplicatereplacer.h"
#include <iostream>
#include <string>

TSPPGODuplicateReplacer::TSPPGODuplicateReplacer(ProblemData* data, Evaluator* evaluator, unsigned int generationFrequency, TSPInitializerRandom* initializer):
	PostGenerationOperator(data, evaluator, generationFrequency), initializer_(initializer)
{
}

void TSPPGODuplicateReplacer::run(RNG* rng, Population* populationNew, Population* populationOld)
{
	float fitnessTracker = populationNew->getSolution(0)->getFitness();
	for (unsigned int i = 1; i < populationNew->size(); i++)
	{
		float fitness = populationNew->getSolution(i)->getFitness();
		if (fitness == fitnessTracker)
		{
			populationNew->replaceSolution(i, initializer_->createSolution());
		}
		else
		{
			fitnessTracker = fitness;
		}
	}
}

void TSPPGODuplicateReplacer::print()
{
	std::cout << "Fitness-Wise Duplicate Solution Replacer (Generation Frequency: " + std::to_string(getGenerationFrequency()) + ")" << std::endl;
}
