#pragma once

#include "population.h"
#include "solution.h"
#include "problemdata.h"
#include "selector.h"
#include "crossoveroperator.h"
#include "mutationoperator.h"
#include "evaluator.h"
#include "rng.h"

#ifdef GALIB_EXPORTS
#define RUNNER_API __declspec(dllexport)
#else
#define RUNNER_API __declspec(dllimport)
#endif

class RUNNER_API GARunner
{
public:
	GARunner(int id, unsigned int subPopulationSize);
	~GARunner();
	int getId();
	void setReferencePopulation(Population* referencePopulation);
	void setSelectors(std::vector<Selector*>* selectors);
	void setCrossoverOperators(std::vector<CrossoverOperator*>* crossoverOperators);
	void setMutationOperators(std::vector<MutationOperator*>* mutationOperators);
	void setEvaluator(Evaluator* evaluator);
	void setSolutionTimeout(long double timeMin);

	void createSubPopulation();
	Population* getSubPopulation();

	virtual void run();
	virtual void terminate();
private:
	virtual void threadFunction();

	int id_;
	unsigned int subPopulationSize_;
	long double timeMin_ = 0;
	Population* referencePopulation_ = nullptr;
	Population* subPopulation_ = nullptr;
	std::vector<Selector*>* selectors_ = nullptr;
	std::vector<CrossoverOperator*>* crossoverOperators_ = nullptr;
	std::vector<MutationOperator*>* mutationOperators_ = nullptr;
	std::vector<unsigned int>* selectorWeights_ = new std::vector<unsigned int>();
	std::vector<unsigned int>* crossoverWeights_ = new std::vector<unsigned int>();
	std::vector<unsigned int>* mutationWeights_ = new std::vector<unsigned int>();
	unsigned int selectorTotal_ = 0;
	unsigned int crossoverTotal_ = 0;
	unsigned int mutationTotal_ = 0;
	Evaluator* evaluator_ = nullptr;

	RNG* rng_;
};

