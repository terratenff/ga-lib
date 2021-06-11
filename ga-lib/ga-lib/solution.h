#pragma once

#include <vector>

#ifdef GALIB_EXPORTS
#define GA_SOLUTION_API __declspec(dllexport)
#else
#define GA_SOLUTION_API __declspec(dllimport)
#endif

class GA_SOLUTION_API Solution
{
public:
	Solution();
	bool operator<(const Solution& other) const;
	bool operator>(const Solution& other) const;
	bool operator==(const Solution& other) const;
	void setFitness(float var);
	void setPenalty(float var);
	float getFitness();
	float getPenalty();
	virtual void print() = 0;
private:
	float fitness_;
	float penalty_;
};