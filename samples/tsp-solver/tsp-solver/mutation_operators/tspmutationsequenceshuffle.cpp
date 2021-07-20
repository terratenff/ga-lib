#include "tspmutationsequenceshuffle.h"
#include "../tspsolution.h"
#include "../tspevaluator.h"
#include <iostream>
#include <string>

TSPMutationSequenceShuffle::TSPMutationSequenceShuffle(ProblemData* data, Evaluator* evaluator, unsigned int useWeight, unsigned int attemptCount, unsigned int resetCount) :
	MutationOperator(data, evaluator, useWeight), attemptCount_(attemptCount), resetCount_(resetCount)
{
}

void TSPMutationSequenceShuffle::run(Solution* offspring, RNG* rng)
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
			fitnessTracker = 0.0f;
		}

		int randSize = rng->rand() % (chromosome.size() / 5);
		int randInsertionPoint = rng->rand() % (chromosome.size() - randSize);

		fitnessOld = static_cast<TSPEvaluator*>(evaluator_)->getPartialEvaluation(offspring, randInsertionPoint, randInsertionPoint + randSize);
		std::random_shuffle(chromosome.begin() + randInsertionPoint, chromosome.begin() + randInsertionPoint + randSize);
		fitnessNew = static_cast<TSPEvaluator*>(evaluator_)->getPartialEvaluation(offspring, randInsertionPoint, randInsertionPoint + randSize);
		fitnessTracker += (fitnessNew - fitnessOld);

		if (fitnessTracker < 0.0f) break;
	}
}

void TSPMutationSequenceShuffle::print()
{
	std::cout << "Sequence Shuffle (Weight: " + std::to_string(getUseWeight()) + ")" << std::endl;
}
