#include "pch.h"
#include "ga.h"
#include <iostream>
#include <limits>
#include <ctime>


GA::GA()
{
}

GA::~GA()
{
	delete problemData_;
	delete population_;
	delete criteria_;
	for (PopulationInitializer* populationInitializer : *populationInitializers_)
	{
		delete populationInitializer;
	}
	populationInitializers_->clear();
	delete populationInitializers_;
	for (Selector* selector : *selectors_)
	{
		delete selector;
	}
	selectors_->clear();
	delete selectors_;
	for (CrossoverOperator* crossoverOperator : *crossoverOperators_)
	{
		delete crossoverOperator;
	}
	crossoverOperators_->clear();
	delete crossoverOperators_;
	for (MutationOperator* mutationOperator : *mutationOperators_)
	{
		delete mutationOperator;
	}
	mutationOperators_->clear();
	delete mutationOperators_;
	delete evaluator_;
}

void GA::setPopulationSize(unsigned int var)
{
	populationSize_ = var;
}

void GA::setThreadCount(unsigned int var)
{
	threadCount_ = var;
}

void GA::setSortOrder(bool reverse)
{
	sortOrder_ = reverse;
}

void GA::setProblemData(ProblemData* problemData)
{
	problemData_ = problemData;
}

void GA::setTerminationCriteria(TerminationCriteria* criteria)
{
	criteria_ = criteria;
}

void GA::setPopulationInitializers(std::vector<PopulationInitializer*>* populationInitializers)
{
	populationInitializers_ = populationInitializers;
}

void GA::setSelectors(std::vector<Selector*>* selectors)
{
	selectors_ = selectors;
}

void GA::setCrossoverOperators(std::vector<CrossoverOperator*>* crossoverOperators)
{
	crossoverOperators_ = crossoverOperators;
}

void GA::setMutationOperators(std::vector<MutationOperator*>* mutationOperators)
{
	mutationOperators_ = mutationOperators;
}

void GA::setEvaluator(Evaluator* evaluator)
{
	evaluator_ = evaluator;
}

void GA::print()
{
	// TODO: Print the following:
	// - Population Size
	// - Number of threads subject to utilization
	// - Termination criteria
	// - Selector details (using Selector print-functions)
	// - Crossover details (using CrossoverOperator print-functions)
	// - Mutation details (using MutationOperator print-functions)
	// - Evaluation details (using Evaluator print-function)
	// - If GA has been used:
	//   - Number of generations utilized
	//   - Amount of time taken
	//   - Discovered optimal solution (using Solution print-function)
}

void GA::run()
{
	std::clock_t clockStart = std::clock();

	// Population Initialization.
	if (populationInitializers_->size() == 1)
	{
		population_ = populationInitializers_->operator[](0)->createPopulation(populationSize_);
	}
	else
	{
		population_ = new Population(populationSize_);
		std::vector<unsigned int> weights = {};
		unsigned int cumulativeWeight = 0;
		for (PopulationInitializer* initializer : *populationInitializers_)
		{
			unsigned int initializerWeight = initializer->getUseWeight();
			cumulativeWeight += initializerWeight;
			weights.push_back(cumulativeWeight);
		}

		for (unsigned int i = 0; i < populationSize_; i++)
		{
			unsigned int initializerSelector = 0;
			unsigned int weight = rand() % (cumulativeWeight + 1);
			for (unsigned int j = 0; j < populationInitializers_->size(); j++)
			{
				if (weights[j] < weight)
				{
					initializerSelector = j;
					break;
				}
			}

			Solution* solution = populationInitializers_->operator[](initializerSelector)->createSolution();
			population_->addSolution(solution);
		}
	}
	population_->setSortOrder(sortOrder_);
	population_->sort();
	population_->assessment();

	createGARunners();

	// Main Loop.

	// TODO

	// Conclusion.

	// TODO

	std::clock_t clockFinish = std::clock();
	time_ = (clockFinish - clockStart) / CLOCKS_PER_SEC;
}

Solution* GA::getBestSolution()
{
	return bestSolutionHistory_->operator[](bestSolutionTracker_);
}

unsigned int GA::getTotalGeneration()
{
	return generation_;
}

long double GA::getTotalTime()
{
	return time_;
}

int GA::getTerminationCode()
{
	return terminationCode_;
}

std::vector<Solution*>* GA::getBestSolutionHistory()
{
	return bestSolutionHistory_;
}

void GA::createGARunners()
{
	// TODO: Single-threaded implementation.
}

void GA::createNewPopulation()
{
	// TODO: Single-threaded implementation.
}

