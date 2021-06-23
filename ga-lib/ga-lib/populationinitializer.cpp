#include "pch.h"
#include "populationinitializer.h"

PopulationInitializer::PopulationInitializer(ProblemData* data, Evaluator* evaluator, unsigned int useWeight):
	data_(data),
	evaluator_(evaluator),
	useWeight_(useWeight)
{
}
