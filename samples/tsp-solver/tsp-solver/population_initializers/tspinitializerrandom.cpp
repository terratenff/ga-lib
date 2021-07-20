#include "tspinitializerrandom.h"
#include <numeric>
#include <algorithm>
#include <iostream>

TSPInitializerRandom::TSPInitializerRandom(ProblemData* data, Evaluator* evaluator, unsigned int useWeight):
	PopulationInitializer(data, evaluator, useWeight)
{
}

Population* TSPInitializerRandom::createPopulation(unsigned int populationSize)
{
	Population* population = new Population(populationSize);
	for (unsigned int i = 0; i < populationSize; i++)
	{
		Solution* solution = createSolution();
		population->addSolution(solution);
	}
	population->assessment();
	return population;
}

Solution* TSPInitializerRandom::createSolution()
{
	TSPSolution* solution = new TSPSolution();
	std::vector<int>& chromosome = solution->getChromosome();
	const unsigned int problemSize = static_cast<TSPData*>(data_)->getProblemSize();
	std::vector<int> subject(problemSize);
	std::iota(subject.begin(), subject.end(), 0);
	std::random_shuffle(subject.begin(), subject.end());
	chromosome = subject;
	evaluator_->evaluateFitness(solution);
	return solution;
}

void TSPInitializerRandom::print()
{
	std::cout << "Random Solution Initializer" << std::endl;
}
