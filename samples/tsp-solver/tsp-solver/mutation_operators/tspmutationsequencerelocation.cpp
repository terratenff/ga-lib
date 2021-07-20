#include "tspmutationsequencerelocation.h"
#include "../tspsolution.h"
#include <iostream>
#include <string>

TSPMutationSequenceRelocation::TSPMutationSequenceRelocation(ProblemData* data, Evaluator* evaluator, unsigned int useWeight, unsigned int attemptCount, unsigned int resetCount):
	MutationOperator(data, evaluator, useWeight), attemptCount_(attemptCount), resetCount_(resetCount)
{
}

void TSPMutationSequenceRelocation::run(Solution* offspring, RNG* rng)
{
	std::vector<int>& chromosome = static_cast<TSPSolution*>(offspring)->getChromosome();
	std::vector<int> backup(chromosome.begin(), chromosome.end());
	float fitnessOld = evaluator_->evaluateFitness(offspring);
	for (unsigned int i = 0; i < attemptCount_; i++)
	{
		if (i % resetCount_ == resetCount_ - 1)
		{
			chromosome.clear();
			chromosome.insert(chromosome.begin(), backup.begin(), backup.end());
		}

		int randSize = rng->rand() % (chromosome.size() / 5);
		int randInsertionPoint = rng->rand() % (chromosome.size() - randSize);

		std::vector<int> gene;
		gene = std::vector<int>(chromosome.begin() + randInsertionPoint, chromosome.begin() + randInsertionPoint + randSize);
		chromosome.erase(chromosome.begin() + randInsertionPoint, chromosome.begin() + randInsertionPoint + randSize);

		int insertionPoint = rng->rand() % chromosome.size();
		chromosome.insert(chromosome.begin() + insertionPoint, gene.begin(), gene.end());

		float fitnessNew = evaluator_->evaluateFitness(offspring);
		if (fitnessNew < fitnessOld) break;
	}
}

void TSPMutationSequenceRelocation::print()
{
	std::cout << "Sequence Relocation (Weight: " + std::to_string(getUseWeight()) + ")" << std::endl;
}
