#pragma once

#include "population.h"
#include "solution.h"
#include "terminationcriteria.h"
#include "garunner.h"
#include "problemdata.h"
#include <vector>
#include <unordered_map>

#ifdef GALIB_EXPORTS
#define GA_API __declspec(dllexport)
#else
#define GA_API __declspec(dllimport)
#endif

class GA_API GA
{
public:
	GA();
	void setPopulationSize(unsigned int var);
	void setThreadCount(unsigned int var);
	void setTerminationCriteria(const TerminationCriteria& criteria);
	virtual void print();
	virtual void run(ProblemData& data);
	Solution& getBestSolution();
	std::vector<Solution>& getBestSolutionHistory();
private:
	void createGARunners();

	unsigned int populationSize_;
	unsigned int threadCount_;
	std::vector<GARunner> runners_;
	Population population_;
	TerminationCriteria criteria_;

	unsigned int generation_;
	unsigned int time_;
	std::vector<Solution> bestSolutionHistory_;
	unsigned int bestSolutionTracker_;
	std::unordered_map<unsigned int, bool> runnerTracker_;

};

