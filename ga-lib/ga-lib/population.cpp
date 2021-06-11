#include "pch.h"
#include "population.h"
#include <algorithm>
#include <numeric>

Population::Population(unsigned int size): bestFitness_(0), worstFitness_(0), averageFitness_(0), varianceFitness_(0)
{
	population_.reserve(size);
}

bool Population::addSolution(const Solution& solution)
{
	if (population_.size() < population_.capacity())
	{
		population_.push_back(solution);
		return true;
	}
	else
	{
		return false;
	}
}

Solution& Population::getSolution(const unsigned int i)
{
	return population_[i];
}

void Population::assessment()
{
	bestFitness_ = (*std::max_element(population_.begin(), population_.end())).getFitness();
	worstFitness_ = (*std::min_element(population_.begin(), population_.end())).getFitness();
	float totalFitness = 0;
	for (Solution& solution : population_)
	{
		totalFitness += solution.getFitness();
	}
	averageFitness_ = totalFitness / population_.size();
	varianceFitness_ = std::abs(bestFitness_ - worstFitness_);
}

void Population::sort(bool reverse)
{
	if (reverse)
	{
		std::sort(population_.rbegin(), population_.rend());
	}
	else
	{
		std::sort(population_.begin(), population_.end());
	}
}

void Population::print()
{
	// TODO
}
