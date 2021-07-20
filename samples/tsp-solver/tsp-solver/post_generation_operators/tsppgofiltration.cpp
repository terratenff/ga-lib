#include "tsppgofiltration.h"
#include <iostream>
#include <string>

TSPPGOFiltration::TSPPGOFiltration(ProblemData* data, Evaluator* evaluator, unsigned int generationFrequency, TSPInitializerRandom* initializer):
	PostGenerationOperator(data, evaluator, generationFrequency), initializer_(initializer)
{
}

void TSPPGOFiltration::run(RNG* rng, Population* populationNew, Population* populationOld)
{
	Population* mergedPopulation = new Population(populationNew->size() + populationOld->size());
	mergedPopulation->mergePopulation(populationNew);
	mergedPopulation->mergePopulation(populationOld, true);
	mergedPopulation->sort();
	float fitnessTracker = mergedPopulation->getSolution(0)->getFitness();
	populationNew->replaceSolution(0, mergedPopulation->getSolution(0), false);
	mergedPopulation->replaceSolution(0, nullptr, false);
	for (unsigned int i = 1; i < populationNew->size(); i++)
	{
		float fitness = mergedPopulation->getSolution(i)->getFitness();
		if (fitness == fitnessTracker)
		{
			populationNew->replaceSolution(i, initializer_->createSolution(), false);
		}
		else
		{
			fitnessTracker = fitness;
			populationNew->replaceSolution(i, mergedPopulation->getSolution(i), false);
		}
		mergedPopulation->replaceSolution(i, nullptr, false);
	}
	delete mergedPopulation;
}

void TSPPGOFiltration::print()
{
	std::cout << "Fitness-Wise Population Filtration (Generation Frequency: " + std::to_string(getGenerationFrequency()) + ")" << std::endl;
}
