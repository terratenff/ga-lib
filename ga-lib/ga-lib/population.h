#pragma once
#include "solution.h"

#ifdef GALIB_EXPORTS
#define GA_POPULATION_API __declspec(dllexport)
#else
#define GA_POPULATION_API __declspec(dllimport)
#endif

class GA_POPULATION_API Population
{
public:
	Population(unsigned int size);
	bool addSolution(const Solution& solution);
	Solution& getSolution(const unsigned int i);
	void assessment();
	void sort(bool reverse);
	virtual void print();
private:
	std::vector<Solution> population_;
	float bestFitness_;
	float worstFitness_;
	float averageFitness_;
	float varianceFitness_;
};

