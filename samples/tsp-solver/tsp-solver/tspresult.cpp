#include "tspresult.h"
#include <iostream>
#include <fstream>

TSPResult::TSPResult(Solution* solution, long double time, int generation, int terminationCode):
	ResultData(solution, time, generation, terminationCode)
{
}

void TSPResult::constructData()
{
	chromosome_ = static_cast<TSPSolution*>(solution_)->getChromosome();
	fitness_ = solution_->getFitness();
	penalty_ = solution_->getPenalty();
}

std::string TSPResult::makeSolutionString()
{
	std::string text = "";
	text += "- Solution Details ---------------------------------------------------------\n";
	text += "Structure: ";
	for (int allele : chromosome_)
	{
		text += std::to_string(allele) + " ";
	}
	text += "\n";
	text += "Fitness:   " + std::to_string(fitness_) + "\n";
	text += "Penalties: " + std::to_string(penalty_) + "\n";
	return text;
}
