#pragma once

#include "problemdata.h"
#include "evaluator.h"
#include "population.h"
#include "solution.h"

#ifdef GALIB_EXPORTS
#define INITIALIZER_API __declspec(dllexport)
#else
#define INITIALIZER_API __declspec(dllimport)
#endif

class INITIALIZER_API PopulationInitializer
{
public:
	PopulationInitializer(ProblemData* data, Evaluator* evaluator, unsigned int useWeight);
	virtual Population* createPopulation() = 0;
	virtual Solution* createSolution() = 0;
private:
	ProblemData* data_;
	Evaluator* evaluator_;
	unsigned int useWeight_;
};

