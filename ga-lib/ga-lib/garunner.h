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

/// <summary>
/// GARunner is an instance of GA that is tasked with the creation of the new population (single-threaded)
/// or a portion of it (multi-threaded). In multithreaded implementations, one runner instance should be
/// managed by one thread. Instances of these should only be created in GA instance's function "createGARunners".
/// </summary>
class RUNNER_API GARunner
{
public:

	/// <summary>
	/// Constructor for a runner instance.
	/// </summary>
	/// <param name="id">Identifying integer.</param>
	/// <param name="subPopulationSize">
	/// Number of individuals that a runner should make.
	/// For example, if set population size is 100 and there are 4 runners, this could be 25 for each runner.
	/// </param>
	GARunner(int id, unsigned int subPopulationSize);
	~GARunner();

	/// <summary>
	/// Getter for the runner's identifying integer.
	/// </summary>
	/// <returns>ID.</returns>
	int getId();

	/// <summary>
	/// Setter for a reference population. Each runner should be assigned the same population as reference,
	/// since they use it to create populations which will be merged later.
	/// </summary>
	/// <param name="referencePopulation">Reference population. This should be GA's current population.</param>
	void setReferencePopulation(Population* referencePopulation);

	/// <summary>
	/// Setter for selectors.
	/// </summary>
	/// <param name="selectors">Collection of selectors. GA instance provides them.</param>
	void setSelectors(std::vector<Selector*>* selectors);

	/// <summary>
	/// Setter for crossover operators.
	/// </summary>
	/// <param name="crossoverOperators">Collection of crossover operators. GA instance provides them.</param>
	void setCrossoverOperators(std::vector<CrossoverOperator*>* crossoverOperators);

	/// <summary>
	/// Setter for mutation operators.
	/// </summary>
	/// <param name="mutationOperators">Collection of mutation operators. GA instance provides them.</param>
	void setMutationOperators(std::vector<MutationOperator*>* mutationOperators);

	/// <summary>
	/// Setter for the evaluator.
	/// </summary>
	/// <param name="evaluator">Evaluator. GA instance provides this.</param>
	void setEvaluator(Evaluator* evaluator);

	/// <summary>
	/// Setter for the duration of time that a runner is allowed to spend in creating new individuals.
	/// If this time is exceeded, the algorithm will be terminated. This is equivalent to minimum time criterion.
	/// </summary>
	/// <param name="timeMin">Minimum time.</param>
	void setSolutionTimeout(long double timeMin);

	/// <summary>
	/// The main function. Creates a population of designated size, but does not return it.
	/// </summary>
	void createSubPopulation();

	/// <summary>
	/// Getter for the population that was created in the function "createSubPopulation".
	/// </summary>
	/// <returns>nullptr prior to invoking "createSubPopulation". Population created by the runner after invoking said function.</returns>
	Population* getSubPopulation();

	/// <summary>
	/// Activates the runner. This is relevant only in multithreaded implementations. When first called, it creates a thread that runs
	/// the function "threadFunction". Any consequent calls signal the thread to make another population. If the runner is in the middle
	/// of creating a population, calling this function should not do anything.
	/// </summary>
	virtual void run();

	/// <summary>
	/// Terminates the runner. This is relevant only in multithreaded implementations. This function should only be called once one or
	/// more termination criteria are met.
	/// </summary>
	virtual void terminate();
private:

	/// <summary>
	/// The main function for the thread that manages the runner. This is relevant only in multithreaded implementations. This function
	/// should not be called by the main thread. The function waits for a condition to be true (set by the function "run"). When that
	/// happens, it calls the function "createSubPopulation". Once that is finished, it sets the aforementioned condition to false.
	/// Then it waits until the condition is true again. A separate condition is used to terminate the thread (using
	/// the function "terminate").
	/// </summary>
	virtual void threadFunction();

	/// <summary>
	/// Identifying integer.
	/// </summary>
	int id_;

	/// <summary>
	/// Number of individuals that should be created by the runner for its population. In the single-threaded implementation,
	/// this is the same as that of the original size. In multithreaded implementations, it is usually set to m/n,
	/// where m is the original size, and n is the number of runners.
	/// </summary>
	unsigned int subPopulationSize_;

	/// <summary>
	/// Minimum time criterion.
	/// </summary>
	long double timeMin_ = 0;

	/// <summary>
	/// Reference population. This should be GA's current population.
	/// </summary>
	Population* referencePopulation_ = nullptr;

	/// <summary>
	/// Population that a runner creates and passes over to the GA instance for merging.
	/// </summary>
	Population* subPopulation_ = nullptr;

	/// <summary>
	/// Collection of selectors. Expected to be received from the GA instance.
	/// </summary>
	std::vector<Selector*>* selectors_ = nullptr;

	/// <summary>
	/// Collection of crossover operators. Expected to be received from the GA instance.
	/// </summary>
	std::vector<CrossoverOperator*>* crossoverOperators_ = nullptr;

	/// <summary>
	/// Collection of mutation operators. Expected to be received from the GA instance.
	/// </summary>
	std::vector<MutationOperator*>* mutationOperators_ = nullptr;

	/// <summary>
	/// Collection of cumulative weights from the selectors. The purpose of this is to
	/// make probability calculations slightly faster.
	/// </summary>
	std::vector<unsigned int>* selectorWeights_ = new std::vector<unsigned int>();

	/// <summary>
	/// Collection of cumulative weights from the crossover operators. The purpose of this is to
	/// make probability calculations slightly faster.
	/// </summary>
	std::vector<unsigned int>* crossoverWeights_ = new std::vector<unsigned int>();

	/// <summary>
	/// Collection of cumulative weights from the mutation operators. The purpose of this is to
	/// make probability calculations slightly faster.
	/// </summary>
	std::vector<unsigned int>* mutationWeights_ = new std::vector<unsigned int>();

	/// <summary>
	/// Total weight value of every selector.
	/// </summary>
	unsigned int selectorTotal_ = 0;

	/// <summary>
	/// Total weight value of every crossover operator.
	/// </summary>
	unsigned int crossoverTotal_ = 0;

	/// <summary>
	/// Total weight value of every mutation operator.
	/// </summary>
	unsigned int mutationTotal_ = 0;

	/// <summary>
	/// Designated evaluator, given by the GA instance.
	/// </summary>
	Evaluator* evaluator_ = nullptr;

	/// <summary>
	/// Random Number Generator. This should be used every time random operations are involved.
	/// </summary>
	RNG* rng_;
};

