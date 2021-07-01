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
	unsigned int getUseWeight();
	virtual void run(Solution* offspring) = 0;
protected:
	ProblemData* data_;
	Evaluator* evaluator_;
private:
	unsigned int useWeight_;
private:

};

