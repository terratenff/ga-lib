#include "pch.h"
#include "solution.h"
#include <iostream>

Solution::Solution(): fitness_(0), penalty_(0)
{
}

bool Solution::operator<(const Solution& other) const
{
	return this->fitness_ - this->penalty_ < other.fitness_ - other.penalty_;
}

bool Solution::operator>(const Solution& other) const
{
	return this->fitness_ - this->penalty_ > other.fitness_ - other.penalty_;
}

bool Solution::operator==(const Solution& other) const
{
	return this->fitness_ - this->penalty_ == other.fitness_ - other.penalty_;
}

void Solution::setFitness(float var)
{
	fitness_ = var;
}

void Solution::setPenalty(float var)
{
	penalty_ = var;
}

float Solution::getFitness()
{
	return fitness_;
}

float Solution::getPenalty()
{
	return penalty_;
}