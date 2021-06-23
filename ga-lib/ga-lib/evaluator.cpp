#include "pch.h"
#include "evaluator.h"

Evaluator::Evaluator(ProblemData* data) : data_(data)
{
}

float Evaluator::evaluatePenalty(Solution* solution)
{
	return 0.0f;
}
