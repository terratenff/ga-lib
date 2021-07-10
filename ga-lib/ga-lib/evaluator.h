#pragma once

#include "problemdata.h"
#include "solution.h"

#ifdef GALIB_EXPORTS
#define EVALUATOR_API __declspec(dllexport)
#else
#define EVALUATOR_API __declspec(dllimport)
#endif

class EVALUATOR_API Evaluator
{
public:
	Evaluator(ProblemData* data);
	virtual float evaluateFitness(Solution* solution) = 0;
	virtual float evaluatePenalty(Solution* solution);
	virtual void print() = 0;
protected:
	ProblemData* data_;
};

