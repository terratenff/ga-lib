#include "pch.h"
#include "postgenerationoperator.h"

PostGenerationOperator::PostGenerationOperator(ProblemData* data, Evaluator* evaluator, unsigned int generationFrequency):
	data_(data),
	evaluator_(evaluator),
	generationFrequency_(generationFrequency)
{
}

unsigned int PostGenerationOperator::getGenerationFrequency()
{
	return generationFrequency_;
}
