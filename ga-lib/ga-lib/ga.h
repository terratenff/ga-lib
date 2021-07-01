#pragma once

#include "population.h"
#include "solution.h"
#include "terminationcriteria.h"
#include "garunner.h"
#include "problemdata.h"
#include "populationinitializer.h"
#include "selector.h"
#include "crossoveroperator.h"
#include "mutationoperator.h"
#include "evaluator.h"
#include "resultdata.h"
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
	~GA();
	void setPopulationSize(unsigned int var);
	void setThreadCount(unsigned int var);
	void setSortOrder(bool reverse);
	void setProblemData(ProblemData* problemData);
	void setTerminationCriteria(TerminationCriteria* criteria);
	void setPopulationInitializers(std::vector<PopulationInitializer*>* populationInitializers);
	void setSelectors(std::vector<Selector*>* selectors);
	void setCrossoverOperators(std::vector<CrossoverOperator*>* crossoverOperators);
	void setMutationOperators(std::vector<MutationOperator*>* mutationOperators);
	void setEvaluator(Evaluator* evaluator);
	void print();
	void run();
	Solution* getBestSolution();
	unsigned int getTotalGeneration();
	long double getTotalTime();

	/// <summary>
	/// Getter for a code integer that is used to determine whether the algorithm was terminated prematurely.
	/// 0: No premature termination / Undefined. 1: A fitness criterion was broken. 2: Minimum generation criterion was broken.
	/// 3: Maximum generation criterion was broken. 4: Minimum time criterion was broken. 5: Maximum time criterion was broken.
	/// None of the above: Something unexpected happened.
	/// </summary>
	int getTerminationCode();
	std::vector<Solution*>* getBestSolutionHistory();
private:
	virtual void createGARunners();
	virtual void createNewPopulation();

	unsigned int populationSize_ = 0;
	unsigned int threadCount_ = 1;
	bool sortOrder_ = false;
	ProblemData* problemData_ = nullptr;
	std::vector<GARunner>* runners_ = nullptr;
	Population* population_ = nullptr;
	TerminationCriteria* criteria_ = nullptr;

	std::vector<PopulationInitializer*>* populationInitializers_ = nullptr;
	std::vector<Selector*>* selectors_ = nullptr;
	std::vector<CrossoverOperator*>* crossoverOperators_ = nullptr;
	std::vector<MutationOperator*>*mutationOperators_ = nullptr;
	Evaluator* evaluator_ = nullptr;

	unsigned int generation_ = 0;
	long double time_ = 0;
	int terminationCode_ = 0;
	std::vector<Solution*>* bestSolutionHistory_ = nullptr;
	unsigned int bestSolutionTracker_ = 0;
	std::unordered_map<unsigned int, bool>* runnerTracker_ = nullptr;

};

