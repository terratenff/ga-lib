#include "pch.h"
#include "crossoveroperator.h"

CrossoverOperator::CrossoverOperator(ProblemData* data, Evaluator* evaluator, unsigned int useWeight) :
	data_(data),
	evaluator_(evaluator),
	useWeight_(useWeight)
{
}

