#include "pch.h"
#include "ga.h"
#include <iostream>
#include <limits>

GA::GA()
{
}

GA::~GA()
{
	delete problemData_;
	delete population_;
	delete criteria_;
	for (unsigned int i = 0; i < selectors_.size(); i++)
	{
		delete selectors_[i];
	}
	selectors_.clear();
	for (unsigned int i = 0; i < crossoverOperators_.size(); i++)
	{
		delete crossoverOperators_[i];
	}
	crossoverOperators_.clear();
	for (unsigned int i = 0; i < mutationOperators_.size(); i++)
	{
		delete mutationOperators_[i];
	}
	mutationOperators_.clear();
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

void GA::setProblemData(ProblemData* problemData)
{
	problemData_ = problemData;
}

void GA::setTerminationCriteria(TerminationCriteria* criteria)
{
	criteria_ = criteria;
}

void GA::setSelectors(std::vector<Selector*> selectors)
{
	selectors_ = selectors;
}

void GA::setCrossoverOperators(std::vector<CrossoverOperator*> crossoverOperators)
{
	crossoverOperators_ = crossoverOperators;
}

void GA::setMutationOperators(std::vector<MutationOperator*> mutationOperators)
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
	// TODO
}

Solution* GA::getBestSolution()
{
	return bestSolutionHistory_[bestSolutionTracker_];
}

std::vector<Solution*> GA::getBestSolutionHistory()
{
	return bestSolutionHistory_;
}

void GA::createGARunners()
{
	// TODO
}


