#pragma once

#include "solution.h"
#include "problemdata.h"
#include "evaluator.h"

#ifdef GALIB_EXPORTS
#define CROSSOVER_API __declspec(dllexport)
#else
#define CROSSOVER_API __declspec(dllimport)
#endif

class CROSSOVER_API CrossoverOperator
{
public:
	CrossoverOperator(ProblemData* data, Evaluator* evaluator, unsigned int useWeight);
	virtual std::pair<Solution*, Solution*> run(Solution* parent1, Solution* parent2) = 0;
private:
	ProblemData* data_;
	Evaluator* evaluator_;
	unsigned int useWeight_;
};

