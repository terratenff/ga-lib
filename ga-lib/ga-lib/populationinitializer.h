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
	unsigned int getUseWeight();
	virtual Population* createPopulation(unsigned int populationSize) = 0;
	virtual Solution* createSolution() = 0;
	virtual void print() = 0;
protected:
	ProblemData* data_;
	Evaluator* evaluator_;
private:
	unsigned int useWeight_;
};

