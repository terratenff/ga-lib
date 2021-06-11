#include "pch.h"
#include "garunner.h"

GARunner::GARunner(int id, int threadCount, Population& targetPopulation):
	id_(id),
	referencePopulation_(targetPopulation),
	subPopulation_({})
{
}

int GARunner::getId()
{
	return id_;
}
