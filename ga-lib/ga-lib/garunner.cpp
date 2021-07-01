#include "pch.h"
#include "garunner.h"

GARunner::GARunner(int id, unsigned int subPopulationSize):
	id_(id),
	subPopulationSize_(subPopulationSize)
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

void GARunner::setSelectors(std::vector<Selector*>* selectors)
{
	selectors_ = selectors;
}

void GARunner::setCrossoverOperators(std::vector<CrossoverOperator*>* crossoverOperators)
{
	crossoverOperators_ = crossoverOperators;
}

void GARunner::setMutationOperators(std::vector<MutationOperator*>* mutationOperators)
{
	mutationOperators_ = mutationOperators;
}

void GARunner::setEvaluator(Evaluator* evaluator)
{
	evaluator_ = evaluator;
}

void GARunner::createSubPopulation()
{
	// TODO
}

Population* GARunner::getSubPopulation()
{
	return subPopulation_;
}

void GARunner::run()
{
	// TODO
}

void GARunner::terminate()
{
	// TODO
}

void GARunner::threadFunction()
{
	// TODO
}

