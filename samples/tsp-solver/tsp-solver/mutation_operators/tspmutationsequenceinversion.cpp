#include "tspmutationsequenceinversion.h"
#include "../tspsolution.h"
#include "../tspevaluator.h"
#include <algorithm>
#include <iostream>
#include <string>

TSPMutationSequenceInversion::TSPMutationSequenceInversion(ProblemData* data, Evaluator* evaluator, unsigned int useWeight, unsigned int attemptCount, unsigned int resetCount):
	MutationOperator(data, evaluator, useWeight), attemptCount_(attemptCount), resetCount_(resetCount)
{
}

void TSPMutationSequenceInversion::run(Solution* offspring, RNG* rng)
{
	std::vector<int>& chromosome = static_cast<TSPSolution*>(offspring)->getChromosome();
	std::vector<int> backup(chromosome.begin(), chromosome.end());
	float fitnessOld, fitnessNew;
	float fitnessTracker = 0.0f;
	for (unsigned int i = 0; i < attemptCount_; i++)
	{
		if (i % resetCount_ == resetCount_ - 1)
		{
			chromosome.clear();
			chromosome.insert(chromosome.begin(), backup.begin(), backup.end());
		}

		int randSize = rng->rand() % (chromosome.size() / 5);
		int randInsertionPoint = rng->rand() % (chromosome.size() - randSize);

		fitnessOld = static_cast<TSPEvaluator*>(evaluator_)->getPartialEvaluation(offspring, randInsertionPoint, randInsertionPoint + randSize);
		std::reverse(chromosome.begin() + randInsertionPoint, chromosome.begin() + randInsertionPoint + randSize);
		fitnessNew = static_cast<TSPEvaluator*>(evaluator_)->getPartialEvaluation(offspring, randInsertionPoint, randInsertionPoint + randSize);
		fitnessTracker += (fitnessNew - fitnessOld);

		if (fitnessTracker < 0) break;
	}
}

void TSPMutationSequenceInversion::print()
{
	std::cout << "Sequence Inversion (Weight: " + std::to_string(getUseWeight()) + ")" << std::endl;
}
