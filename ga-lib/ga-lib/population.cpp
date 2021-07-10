#include "pch.h"
#include "population.h"
#include <algorithm>
#include <numeric>
#include <limits>
#include <stdexcept>
#include <iostream>
#include <string>

Population::Population(unsigned int size):
	population_(new std::vector<Solution*>()),
	lowestFitness_(0),
	highestFitness_(0),
	averageFitness_(0),
	varianceFitness_(0)
{
	population_->reserve(size);
}

Population::~Population()
{
	for (Solution* solution : *population_)
	{
		if (solution != nullptr) delete solution;
	}
	population_->clear();
	delete population_;
}

void Population::setSortOrder(bool reverse)
{
	sortOrder_ = reverse;
}

bool Population::getSortOrder()
{
	return sortOrder_;
}

void Population::addSolution(Solution* solution, bool suppressException)
{
	if (population_->size() < population_->capacity())
	{
		population_->push_back(solution);
	}
	else if (!suppressException)
	{
		throw std::out_of_range("Population size exceeded set limit");
	}
}

Solution* Population::getSolution(unsigned int i)
{
	return population_->operator[](i);
}

void Population::replaceSolution(unsigned int i, Solution* solution)
{
	Solution* subject = population_->operator[](i);
	delete subject;
	population_->operator[](i) = solution;
}

const unsigned int Population::size() const
{
	return population_->size();
}

void Population::assessment()
{
	highestFitness_ = -std::numeric_limits<float>::infinity();
	lowestFitness_ = std::numeric_limits<float>::infinity();
	float totalFitness = 0;
	for (Solution* solution : *population_)
	{
		float solutionFitness = solution->getFitness();
		totalFitness += solutionFitness;
		if (solutionFitness > highestFitness_) highestFitness_ = solutionFitness;
		if (solutionFitness < lowestFitness_) lowestFitness_ = solutionFitness;
	}
	averageFitness_ = totalFitness / population_->size();
	varianceFitness_ = std::abs(lowestFitness_ - highestFitness_);
}

void Population::sort()
{
	if (sortOrder_)
	{
		std::sort(population_->begin(), population_->end(), [](Solution* lhs, Solution* rhs) {
			return lhs > rhs;
		});
	}
	else
	{
		std::sort(population_->begin(), population_->end(), [](Solution* lhs, Solution* rhs) {
			return lhs < rhs;
		});
	}
}

void Population::clear()
{
	for (Solution* solution : *population_)
	{
		delete solution;
	}
	population_->clear();
}

void Population::print()
{
	std::cout << "Population Details" << std::endl << "----------------------------" << std::endl;
	std::cout << "Size:                  " + std::to_string(population_->size()) << std::endl;
	std::cout << "Lowest Fitness Value:  " + std::to_string(lowestFitness_) << std::endl;
	std::cout << "Highest Fitness Value: " + std::to_string(highestFitness_) << std::endl;
	std::cout << "Average Fitness Value: " + std::to_string(averageFitness_) << std::endl;
	std::cout << "Fitness Variance:      " + std::to_string(varianceFitness_) << std::endl;
}
