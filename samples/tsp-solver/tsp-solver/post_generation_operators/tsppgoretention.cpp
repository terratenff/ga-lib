#include "tsppgoretention.h"
#include <numeric>
#include <iostream>
#include <string>

TSPPGORetention::TSPPGORetention(ProblemData* data, Evaluator* evaluator, unsigned int generationFrequency, float retentionRate):
	PostGenerationOperator(data, evaluator, generationFrequency), retentionRate_(retentionRate)
{
}

void TSPPGORetention::run(RNG* rng, Population* populationNew, Population* populationOld)
{
	unsigned int subjectCount = unsigned int(populationOld->size() * retentionRate_);
	std::vector<unsigned int> indices(populationOld->size());
	std::iota(indices.begin(), indices.end(), 0);
	std::random_shuffle(indices.begin(), indices.end());
	for (unsigned int i = 0; i < subjectCount; i++)
	{
		unsigned int targetIndex = indices[i];
		Solution* solution = populationOld->getSolution(targetIndex)->clone();
		populationNew->replaceSolution(targetIndex, solution, true);
	}
}

void TSPPGORetention::print()
{
	std::cout << "Prior Population Retention (Generation Frequency: " + std::to_string(getGenerationFrequency()) + ", Retention Rate: " + std::to_string(retentionRate_) + ")" << std::endl;
}
