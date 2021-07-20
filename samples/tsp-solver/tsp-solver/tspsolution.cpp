#include "tspsolution.h"
#include <iostream>
#include <string>

TSPSolution::~TSPSolution()
{
	chromosome_.clear();
}

Solution* TSPSolution::clone()
{
	TSPSolution* solution = new TSPSolution();
	solution->chromosome_ = this->chromosome_;
	solution->setFitness(this->getFitness());
	solution->setPenalty(this->getPenalty());
	return solution;
}

void TSPSolution::print()
{
	std::cout << "Solution (Fitness: " + std::to_string(getFitness()) + "): " << std::endl;
	for (int allele : chromosome_)
	{
		std::cout << std::to_string(allele) + " ";
	}
	std::cout << std::endl;
}

std::vector<int>& TSPSolution::getChromosome()
{
	return chromosome_;
}
