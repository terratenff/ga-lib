#pragma once

#include "solution.h"
#include <vector>

/// <summary>
/// Representation of a solution to the normal TSP.
/// </summary>
class TSPSolution: public Solution
{
public:
	~TSPSolution();
	Solution* clone() override;
	void print() override;
	std::vector<int>& getChromosome();
private:
	std::vector<int> chromosome_ = {};
};

