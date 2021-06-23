#pragma once

#include "population.h"
#include "solution.h"
#include "problemdata.h"
#include "selector.h"
#include "crossoveroperator.h"
#include "mutationoperator.h"
#include "evaluator.h"
#include <thread>
#include <future>

#ifdef GALIB_EXPORTS
#define RUNNER_API __declspec(dllexport)
#else
#define RUNNER_API __declspec(dllimport)
#endif

class RUNNER_API GARunner
{
public:
	GARunner(int id);
	~GARunner();
	int getId();
	void setReferencePopulation(Population* referencePopulation);
	void setSelectors(std::vector<Selector*> selectors);
	void setCrossoverOperators(std::vector<CrossoverOperator*> crossoverOperators);
	void setMutationOperators(std::vector<MutationOperator*> mutationOperators);
	void setEvaluator(Evaluator* evaluator);

	void run();
	void terminate();
	void join();
	Population* getSubPopulation();
private:
	void threadFunction();
	void createSubPopulation();

	int id_;
	Population* referencePopulation_ = nullptr;
	Population* subPopulation_ = nullptr;
	std::vector<Selector*> selectors_ = {};
	std::vector<CrossoverOperator*> crossoverOperators_ = {};
	std::vector<MutationOperator*> mutationOperators_ = {};
	Evaluator* evaluator_ = nullptr;

	std::thread runnerThread_;
	std::promise<bool> subPopulationPromise_;
	std::shared_future<bool> startFuture_;
	std::shared_future<bool> endFuture_;
	bool isStarted_ = false;
	bool terminated_ = false;
};

