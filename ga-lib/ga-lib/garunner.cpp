#include "pch.h"
#include "garunner.h"

GARunner::GARunner(int id):
	id_(id)
{
}

GARunner::~GARunner()
{
	delete subPopulation_;
}

int GARunner::getId()
{
	return id_;
}

void GARunner::setReferencePopulation(Population* referencePopulation)
{
	referencePopulation_ = referencePopulation;
}

void GARunner::setSelectors(std::vector<Selector*> selectors)
{
	selectors_ = selectors;
}

void GARunner::setCrossoverOperators(std::vector<CrossoverOperator*> crossoverOperators)
{
	crossoverOperators_ = crossoverOperators;
}

void GARunner::setMutationOperators(std::vector<MutationOperator*> mutationOperators)
{
	mutationOperators_ = mutationOperators;
}

void GARunner::setEvaluator(Evaluator* evaluator)
{
	evaluator_ = evaluator;
}

void GARunner::run()
{
	if (!isStarted_)
	{
		isStarted_ = true;
		runnerThread_ = std::thread(&GARunner::threadFunction, this);
	}
}

void GARunner::terminate()
{
	terminated_ = true;
}

void GARunner::join()
{
	runnerThread_.join();
}

Population* GARunner::getSubPopulation()
{
	return subPopulation_;
}

void GARunner::threadFunction()
{
	while (!terminated_)
	{
		// TODO
	}
}

void GARunner::createSubPopulation()
{
	// TODO
}
