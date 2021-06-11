#include "pch.h"
#include "ga.h"
#include <iostream>
#include <limits>

GA::GA() :
	populationSize_(100),
	threadCount_(1),
	runners_({}),
	population_(Population(100)),
	criteria_(TerminationCriteria(100, 1000, 5, 60, -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity())),
	bestSolutionHistory_({}),
	bestSolutionTracker_(0)
{
}

void GA::setPopulationSize(unsigned int var)
{
	populationSize_ = var;
}

void GA::setThreadCount(unsigned int var)
{
	threadCount_ = var;
}

void GA::setTerminationCriteria(const TerminationCriteria& criteria)
{
	criteria_ = criteria;
}

void GA::print()
{
	// TODO
}

void GA::run(ProblemData& data)
{
	// TODO
}

Solution& GA::getBestSolution()
{
	return bestSolutionHistory_[bestSolutionTracker_];
}

std::vector<Solution>& GA::getBestSolutionHistory()
{
	return bestSolutionHistory_;
}

void GA::createGARunners()
{
	// TODO
}


