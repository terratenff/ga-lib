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
	unsigned int getUseWeight();
	virtual std::pair<Solution*, Solution*> run(Solution* parent1, Solution* parent2) = 0;
	virtual void print() = 0;
protected:
	ProblemData* data_;
	Evaluator* evaluator_;
private:
	unsigned int useWeight_;
};

