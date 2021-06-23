#pragma once

#include "solution.h"
#include "problemdata.h"
#include "evaluator.h"

#ifdef GALIB_EXPORTS
#define MUTATION_API __declspec(dllexport)
#else
#define MUTATION_API __declspec(dllimport)
#endif

class MUTATION_API MutationOperator
{
public:
	MutationOperator(ProblemData* data, Evaluator* evaluator, unsigned int useWeight);
	virtual void run(Solution* offspring) = 0;
private:
	ProblemData* data_;
	Evaluator* evaluator_;
	unsigned int useWeight_;
private:

};

