#include "pch.h"
#include "population.h"
#include <algorithm>
#include <numeric>
#include <stdexcept>

Population::Population(unsigned int size): bestFitness_(0), worstFitness_(0), averageFitness_(0), varianceFitness_(0)
{
	population_.reserve(size);
}

Population::~Population()
{
	for (Solution* solution : population_)
	{
		delete solution;
	}
	population_.clear();
}

void Population::addSolution(Solution* solution)
{
	if (population_.size() < population_.capacity())
	{
		population_.push_back(solution);
	}
	else
	{
		throw std::out_of_range("Population size exceeded set limit");
	}
}

Solution* Population::getSolution(unsigned int i)
{
	return population_[i];
}

void Population::assessment()
{
	bestFitness_ = (*std::max_element(population_.begin(), population_.end()))->getFitness();
	worstFitness_ = (*std::min_element(population_.begin(), population_.end()))->getFitness();
	float totalFitness = 0;
	for (Solution* solution : population_)
	{
		totalFitness += solution->getFitness();
	}
	averageFitness_ = totalFitness / population_.size();
	varianceFitness_ = std::abs(bestFitness_ - worstFitness_);
}

void Population::sort(bool reverse)
{
	if (reverse)
	{
		std::sort(population_.begin(), population_.end(), [](Solution* lhs, Solution* rhs) {
			return lhs->getFitness() > rhs->getFitness();
		});
	}
	else
	{
		std::sort(population_.begin(), population_.end(), [](Solution* lhs, Solution* rhs) {
			return lhs->getFitness() < rhs->getFitness();
			});
	}
}

void Population::clear()
{
	for (Solution* solution : population_)
	{
		delete solution;
	}
	population_.clear();
}

void Population::print()
{
	// TODO
}
