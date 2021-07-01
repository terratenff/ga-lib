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
	~Population();
	void setSortOrder(bool reverse);
	bool getSortOrder();
	void addSolution(Solution* solution);
	Solution* getSolution(unsigned int i);
	void replaceSolution(unsigned int i, Solution* solution);
	const unsigned int size() const;
	void assessment();
	void sort();
	void clear();
	virtual void print();
private:
	std::vector<Solution*>* population_;
	bool sortOrder_ = false;
	float lowestFitness_;
	float highestFitness_;
	float averageFitness_;
	float varianceFitness_;
};

