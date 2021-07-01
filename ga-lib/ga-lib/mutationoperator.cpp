#include "pch.h"
#include "mutationoperator.h"

MutationOperator::MutationOperator(ProblemData* data, Evaluator* evaluator, unsigned int useWeight) :
	data_(data),
	evaluator_(evaluator),
	useWeight_(useWeight)
{
}

unsigned int MutationOperator::getUseWeight()
{
	return useWeight_;
}

