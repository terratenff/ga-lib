#pragma once

#include "population.h"
#include "solution.h"
#include "terminationcriteria.h"
#include "garunner.h"
#include "problemdata.h"
#include "selector.h"
#include "crossoveroperator.h"
#include "mutationoperator.h"
#include "evaluator.h"
#include <vector>
#include <memory>
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
	~GA();
	void setPopulationSize(unsigned int var);
	void setThreadCount(unsigned int var);
	void setProblemData(ProblemData* problemData);
	void setTerminationCriteria(TerminationCriteria* criteria);
	void setSelectors(std::vector<Selector*> selectors);
	void setCrossoverOperators(std::vector<CrossoverOperator*> crossoverOperators);
	void setMutationOperators(std::vector<MutationOperator*> mutationOperators);
	void setEvaluator(Evaluator* evaluator);
	void print();
	void run();
	Solution* getBestSolution();
	std::vector<Solution*> getBestSolutionHistory();
private:
	void createGARunners();

	unsigned int populationSize_ = 0;
	unsigned int threadCount_ = 1;
	ProblemData* problemData_ = nullptr;
	std::vector<GARunner> runners_ = {};
	Population* population_ = nullptr;
	TerminationCriteria* criteria_ = nullptr;

	std::vector<Selector*> selectors_ = {};
	std::vector<CrossoverOperator*> crossoverOperators_ = {};
	std::vector<MutationOperator*> mutationOperators_ = {};
	Evaluator* evaluator_ = nullptr;

	unsigned int generation_ = 0;
	unsigned int time_ = 0;
	std::vector<Solution*> bestSolutionHistory_ = {};
	unsigned int bestSolutionTracker_ = 0;
	std::unordered_map<unsigned int, bool> runnerTracker_ = {};

};

