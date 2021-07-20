#include "tsppgoelitism.h"
#include <iostream>
#include <string>

TSPPGOElitism::TSPPGOElitism(ProblemData* data, Evaluator* evaluator, unsigned int generationFrequency, float retentionRate) :
	PostGenerationOperator(data, evaluator, generationFrequency), retentionRate_(retentionRate)
{
}

void TSPPGOElitism::run(RNG* rng, Population* populationNew, Population* populationOld)
{
	unsigned int subjectCount = unsigned int(populationOld->size() * retentionRate_);
	unsigned int elitismCount = getHistorySize();

	populationNew->sort();
	populationNew->replaceSolution(populationNew->size() - 1, getBestSolution()->clone(), true);
	for (unsigned int i = 0; i < subjectCount; i++)
	{
		unsigned int targetIndex = rng->rand() % elitismCount;
		unsigned int insertionPoint = populationNew->size() - 2 - i;
		Solution* solution = getFromSolutionHistory(targetIndex)->clone();
		populationNew->replaceSolution(insertionPoint, solution, true);
	}
}

void TSPPGOElitism::print()
{
	std::cout << "Elitism Retention (Generation Frequency: " + std::to_string(getGenerationFrequency()) + ", Retention Rate: " + std::to_string(retentionRate_) + ")" << std::endl;
}
