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
	unsigned int getGenerationFrequency();
	virtual void run(Population* populationNew, Population* populationOld = nullptr) = 0;
	virtual void print() = 0;
protected:
	ProblemData* data_;
	Evaluator* evaluator_;
private:
	unsigned int generationFrequency_;
};

