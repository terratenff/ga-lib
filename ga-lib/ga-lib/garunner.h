#pragma once

#include "population.h"
#include "solution.h"

#ifdef GALIB_EXPORTS
#define RUNNER_API __declspec(dllexport)
#else
#define RUNNER_API __declspec(dllimport)
#endif

class RUNNER_API GARunner
{
public:
	GARunner(int id, int threadCount, Population& targetPopulation);
	int getId();
	// TODO: Function that creates a sub-population using reference population.
private:
	int id_;
	Population& referencePopulation_;
	Population subPopulation_;
	// TODO: References to the following.
	// - Selector
	// - CrossoverOperator
	// - MutationOperator
	// - Evaluator
};

