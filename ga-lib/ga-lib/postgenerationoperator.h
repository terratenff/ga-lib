#pragma once

#include "problemdata.h"
#include "evaluator.h"
#include "population.h"

#ifdef GALIB_EXPORTS
#define POSTGENERATION_API __declspec(dllexport)
#else
#define POSTGENERATION_API __declspec(dllimport)
#endif

class POSTGENERATION_API PostGenerationOperator
{
public:
	PostGenerationOperator(ProblemData* data, Evaluator* evaluator, unsigned int generationFrequency);
	virtual void run(Population* population) = 0;
private:
	ProblemData* data_;
	Evaluator* evaluator_;
	unsigned int generationFrequency_;
};

