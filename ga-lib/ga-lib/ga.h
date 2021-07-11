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
#include "postgenerationoperator.h"
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
	void addPopulationInitializer(PopulationInitializer* populationInitializer);
	void addSelector(Selector* selector);
	void addCrossoverOperator(CrossoverOperator* crossoverOperator);
	void addMutationOperator(MutationOperator* mutationOperator);
	void addPostGenerationOperator(PostGenerationOperator* postGenerationOperator);
	void setEvaluator(Evaluator* evaluator);
	void print();
	void run();
	Solution* getBestSolution();
	unsigned int getTotalGeneration();
	long double getTotalTime();

	/// <summary>
	/// Getter for a code integer that is used to determine whether the algorithm was terminated prematurely.
	/// -1: Algorithm has not been run yet. 0: No premature termination / Undefined. 1: A fitness criterion was broken.
	/// 2: Minimum generation criterion was broken. 3: Maximum generation criterion was broken. 4: Minimum time criterion was broken.
	/// 5: Maximum time criterion was broken. None of the above: Something unexpected happened.
	/// </summary>
	int getTerminationCode();
	std::vector<Solution*>* getBestSolutionHistory();
private:
	virtual void createGARunners();
	virtual Population* createNewPopulation();

	unsigned int populationSize_ = 0;
	unsigned int threadCount_ = 1;
	bool sortOrder_ = false;
	ProblemData* problemData_ = nullptr;
	std::vector<GARunner*>* runners_ = new std::vector<GARunner*>();
	Population* population_ = nullptr;
	TerminationCriteria* criteria_ = nullptr;

	std::vector<PopulationInitializer*>* populationInitializers_ = new std::vector<PopulationInitializer*>();
	std::vector<Selector*>* selectors_ = new std::vector<Selector*>();
	std::vector<CrossoverOperator*>* crossoverOperators_ = new std::vector<CrossoverOperator*>();
	std::vector<MutationOperator*>* mutationOperators_ = new std::vector<MutationOperator*>();
	std::vector<PostGenerationOperator*>* postGenerationOperators_ = new std::vector<PostGenerationOperator*>();
	Evaluator* evaluator_ = nullptr;

	unsigned int generation_ = 0;
	unsigned int generationMin_ = 0;
	long double time_ = 0;
	int terminationCode_ = -1;
	std::vector<Solution*>* bestSolutionHistory_ = new std::vector<Solution*>();
	unsigned int bestSolutionTracker_ = 0;
	std::unordered_map<unsigned int, bool>* runnerTracker_ = nullptr;

};

