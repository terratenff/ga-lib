#include "tspmutationswap.h"
#include "../tspsolution.h"
#include "../tspevaluator.h"
#include <iostream>
#include <string>

TSPMutationSwap::TSPMutationSwap(ProblemData* data, Evaluator* evaluator, unsigned int useWeight, unsigned int attemptCount):
	MutationOperator(data, evaluator, useWeight), attemptCount_(attemptCount)
{
}

void TSPMutationSwap::run(Solution* offspring, RNG* rng)
{
	std::vector<int>& chromosome = static_cast<TSPSolution*>(offspring)->getChromosome();
	std::vector<int> backup(chromosome.begin(), chromosome.end());
	for (unsigned int i = 0; i < attemptCount_; i++)
	{
		int rand1 = (rng->rand() % (chromosome.size() - 2)) + 1;
		int rand2 = (rng->rand() % (chromosome.size() - 2)) + 1;
		int indexDifference = std::abs(rand1 - rand2);
		if (indexDifference == 1 || indexDifference == 2)
		{
			// Selected indices are sufficiently close to each other.
			float fitnessOld, fitnessNew;
			if (rand1 < rand2)
			{
				fitnessOld = static_cast<TSPEvaluator*>(evaluator_)->getPartialEvaluation(offspring, rand1 - 1, rand2 + 1);
			}
			else
			{
				fitnessOld = static_cast<TSPEvaluator*>(evaluator_)->getPartialEvaluation(offspring, rand2 - 1, rand1 + 1);
			}

			std::swap(chromosome[rand1], chromosome[rand2]);

			if (rand1 < rand2)
			{
				fitnessNew = static_cast<TSPEvaluator*>(evaluator_)->getPartialEvaluation(offspring, rand1 - 1, rand2 + 1);
			}
			else
			{
				fitnessNew = static_cast<TSPEvaluator*>(evaluator_)->getPartialEvaluation(offspring, rand2 - 1, rand1 + 1);
			}
			if (fitnessNew < fitnessOld) break;
		}
		else if (rand1 == rand2)
		{
			// Selected indices are the same.
			continue;
		}
		else
		{
			// Selected indices are far away from each other.
			float fitnessOld1 = static_cast<TSPEvaluator*>(evaluator_)->getPartialEvaluation(offspring, rand1 - 1, rand1 + 1);
			float fitnessOld2 = static_cast<TSPEvaluator*>(evaluator_)->getPartialEvaluation(offspring, rand2 - 1, rand2 + 1);
			std::swap(chromosome[rand1], chromosome[rand2]);
			float fitnessNew1 = static_cast<TSPEvaluator*>(evaluator_)->getPartialEvaluation(offspring, rand1 - 1, rand1 + 1);
			float fitnessNew2 = static_cast<TSPEvaluator*>(evaluator_)->getPartialEvaluation(offspring, rand2 - 1, rand2 + 1);
			if (fitnessNew1 + fitnessNew2 < fitnessOld1 + fitnessOld2) break;
		}
		
		// The swap did not improve the solution. The change will be undone here (unless it is the last attempt).
		if (i != attemptCount_ - 1)
		{
			std::swap(chromosome[rand2], chromosome[rand1]);
		}
	}
}

void TSPMutationSwap::print()
{
	std::cout << "Evaluated Swap (Weight: " + std::to_string(getUseWeight()) + ", Maximum attempt count: " + std::to_string(attemptCount_) + ")" << std::endl;
}
