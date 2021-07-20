#pragma once

#include "resultdata.h"
#include "tspsolution.h"
#include <string>

/// <summary>
/// Result instance for the normal TSP. Includes a chromosome and its evaluated fitness and penalty.
/// </summary>
class TSPResult : public ResultData
{
public:
	TSPResult(Solution* solution, long double time, int generation, int terminationCode = 0);
private:
	void constructData() override;
	std::string makeSolutionString() override;
	std::vector<int> chromosome_ = {};
	float fitness_ = 0;
	float penalty_ = 0;
};

