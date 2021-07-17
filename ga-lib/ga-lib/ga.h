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

#ifdef GALIB_EXPORTS
#define GA_API __declspec(dllexport)
#else
#define GA_API __declspec(dllimport)
#endif

/// <summary>
/// Genetic Algorithm (GA) is a metaheuristic, population-based algorithm.
/// Population consists of individuals that present solutions to the presented problem.
/// The solutions themselves are often called chromosomes.
/// GA functions in the following fashion:
/// 1. GA first initializes a population of individuals. The way these are created depends on the population initializers that have
/// been given to the GA instance. The population initializers must also evaluate the individuals (they are given access to the evaluator).
/// 2. The main loop begins. It is a nested loop where the inner loop creates two new individual (takes place in GARunner), and the outer loop
/// creates the population. The following steps are taken to create a pair of new individuals:
/// 2a. Two individuals from the current population are selected (using Selector-instances) to act as parents.
/// 2b. A crossover is performed with the parents. This results in two offspring that share genetic information with their parents.
/// This is usually given a high probability of occurring.
/// 2c. A mutation is performed with both offspring. In so doing, their genetic information is modified slightly, resulting in genetic
/// diversification. This is done in an attempt to not coverge to a local maxima/minima. Mutation is usually given a low probability of occurring.
/// 2d. One last evaluation is performed for the offspring (in case this wasn't done in crossover/mutation). Then they are added to the new
/// population.
/// 3. Once a new population has been created, optional post-generation operations are performed. After that, the new population replaces the
/// current operation. Then a new generation begins (back to step 2).
/// 4. Steps 2-3 are repeated until one or more conditions set by the termination criteria are met.
/// It should be noted that this class provides single-threaded implementation. For multithreading, create a derived class and implement
/// virtual functions "createGARunners" and "createNewPopulation". See their documentation for more details.
/// </summary>
class GA_API GA
{
public:

	/// <summary>
	/// Constructor for the GA instance. Only one is needed.
	/// </summary>
	GA();
	~GA();

	/// <summary>
	/// Setter for the size of the population. Default population size is 100.
	/// </summary>
	/// <param name="var">Population size.</param>
	void setPopulationSize(unsigned int var);

	/// <summary>
	/// Setter for the number of threads that are to be used. This translates to the number of GARunners that will be used.
	/// This is only relevant in multithreaded implementations. In a GA instance changing this does nothing.
	/// Default thread count is 1.
	/// </summary>
	/// <param name="var">Number of threads.</param>
	void setThreadCount(unsigned int var);

	/// <summary>
	/// Setter for which direction should be taken while sorting populations and comparing population individuals.
	/// Default sort order is from lowest to highest (false).
	/// </summary>
	/// <param name="reverse">true = reversed (the higher value, the better). false = normal (the lower value, the better)</param>
	void setSortOrder(bool reverse);

	/// <summary>
	/// Setter for the flag that determines whether the GA instance should keep the user updated on the progress of the execution
	/// (via prints). Also applies to population initialization.
	/// Print state is true by default.
	/// </summary>
	/// <param name="enabled">true = For each generation, information is given about generation and fitness. false = Nothing is printed.</param>
	void setPrintState(bool enabled);

	/// <summary>
	/// Setter for the pseudo random number generator. The base class RNG can be used, but it is not recommended in multithreaded implementations.
	/// </summary>
	/// <param name="rng">Pseudo random number generator. Base class uses "std::rand()".</param>
	void setRandomNumberGenerator(RNG* rng);

	/// <summary>
	/// Setter for problem data.
	/// </summary>
	/// <param name="problemData">Information related to the problem that is to be solved.</param>
	void setProblemData(ProblemData* problemData);

	/// <summary>
	/// Setter for the termination criteria.
	/// </summary>
	/// <param name="criteria">Collection of conditions that are used to determine when the algorithm should be terminated.</param>
	void setTerminationCriteria(TerminationCriteria* criteria);

	/// <summary>
	/// Adds a population initializer for the GA instance to use.
	/// </summary>
	/// <param name="populationInitializer">Population initializer. Creates a population for generation 0.</param>
	void addPopulationInitializer(PopulationInitializer* populationInitializer);

	/// <summary>
	/// Adds a selector for the GA instance to use.
	/// </summary>
	/// <param name="selector">Selector. Selects population individuals to act as parents for the crossover operation.</param>
	void addSelector(Selector* selector);

	/// <summary>
	/// Adds a crossover operator for the GA instance to use.
	/// </summary>
	/// <param name="crossoverOperator">Crossover operator. Performs a crossover operation.</param>
	void addCrossoverOperator(CrossoverOperator* crossoverOperator);

	/// <summary>
	/// Adds a mutation operator for the GA instance to use.
	/// </summary>
	/// <param name="mutationOperator">Mutation operator. Mutates the chromosome of a population individual.</param>
	void addMutationOperator(MutationOperator* mutationOperator);

	/// <summary>
	/// Adds a post-generation operator for the GA instance to use.
	/// </summary>
	/// <param name="postGenerationOperator">Post-generation operator. Adjusts recently created population in a user-specified manner.</param>
	void addPostGenerationOperator(PostGenerationOperator* postGenerationOperator);

	/// <summary>
	/// Setter for an evaluator.
	/// </summary>
	/// <param name="evaluator">Evaluator. Evaluates population individuals using problem data as reference.</param>
	void setEvaluator(Evaluator* evaluator);

	/// <summary>
	/// Designated print-function for the GA instance. Shows general information about the GA instance.
	/// </summary>
	void print();

	/// <summary>
	/// Initiates the GA. Note that GA has to be configured before it is run.
	/// The minimum that has to be done is to set problem data, termination criteria, population initializers, selectors,
	/// crossover operators, mutation operators and an evaluator.
	/// </summary>
	void run();

	/// <summary>
	/// Collects the best overall individual that GA has found during its execution.
	/// </summary>
	/// <returns>Individual that has the most optimal discovered solution.</returns>
	Solution* getBestSolution();

	/// <summary>
	/// Getter for the number of generations that have been iterated during the entire GA execution.
	/// </summary>
	/// <returns>Total number of generations iterated.</returns>
	unsigned int getTotalGeneration();

	/// <summary>
	/// Getter for the amount of time that the entire GA execution lasted for.
	/// </summary>
	/// <returns>Total elapsed time.</returns>
	long double getTotalTime();

	/// <summary>
	/// Getter for a code integer that is used to determine whether the algorithm was terminated prematurely.
	/// </summary>
	/// <returns>
	/// -1: Algorithm has not been run yet. 0: No premature termination / Undefined. 1: A fitness criterion was broken.
	/// 2: Minimum generation criterion was broken. 3: Maximum generation criterion was broken. 4: Minimum time criterion was broken.
	/// 5: Maximum time criterion was broken. None of the above: Something unexpected happened.
	/// </returns>
	int getTerminationCode();

	/// <summary>
	/// Getter for the collection of individuals that are the best of their generations.
	/// </summary>
	/// <returns>Best solution history.</returns>
	std::vector<Solution*>* getBestSolutionHistory();
private:

	/// <summary>
	/// Creates the runners that GA uses to create new populations.
	/// This function, along with "createNewPopulation", has to be overridden
	/// if multithreading is to be implemented.
	/// </summary>
	virtual void createGARunners();

	/// <summary>
	/// Creates a new population for the next generation to use.
	/// This function, along with "createGARunners", has to be overridden
	/// if multithreading is to be implemented.
	/// </summary>
	/// <returns>New population.</returns>
	virtual Population* createNewPopulation();

	/// <summary>
	/// Number of individuals that populations are allowed to have.
	/// Exceeding this results in an exception being thrown.
	/// </summary>
	unsigned int populationSize_ = 100;

	/// <summary>
	/// Number of threads that are to be used.
	/// This only matters in multithreaded implementations.
	/// </summary>
	unsigned int threadCount_ = 1;

	/// <summary>
	/// Determines the direction of population sorting and individual comparisons.
	/// If true, order is from highest to lowest. If false, lowest to highest.
	/// </summary>
	bool sortOrder_ = false;

	/// <summary>
	/// Flag that determines whether GA instance should print information about
	/// its execution every generation (and initialization).
	/// </summary>
	bool printState_ = true;

	/// <summary>
	/// Pseudo random number generator. Runner instances are given copies of these with different seeds.
	/// </summary>
	RNG* rng_ = nullptr;

	/// <summary>
	/// Instance of problem data. Contains information that is relevant to the problem that is to be solved.
	/// </summary>
	ProblemData* problemData_ = nullptr;

	/// <summary>
	/// Collection of runners that are in charge of creating a new population.
	/// </summary>
	std::vector<GARunner*>* runners_ = new std::vector<GARunner*>();

	/// <summary>
	/// Population from which new populations are created.
	/// </summary>
	Population* population_ = nullptr;

	/// <summary>
	/// Collection of conditions that are used to determine when the algorithm should be terminated.
	/// </summary>
	TerminationCriteria* criteria_ = nullptr;

	/// <summary>
	/// Collection of population initializers that GA is allowed to use.
	/// </summary>
	std::vector<PopulationInitializer*>* populationInitializers_ = new std::vector<PopulationInitializer*>();

	/// <summary>
	/// Collection of selectors that GA is allowed to use.
	/// </summary>
	std::vector<Selector*>* selectors_ = new std::vector<Selector*>();

	/// <summary>
	/// Collection of crossover operators that GA is allowed to use.
	/// </summary>
	std::vector<CrossoverOperator*>* crossoverOperators_ = new std::vector<CrossoverOperator*>();

	/// <summary>
	/// Collection of mutation operators that GA is allowed to use.
	/// </summary>
	std::vector<MutationOperator*>* mutationOperators_ = new std::vector<MutationOperator*>();

	/// <summary>
	/// Collection of post-generation operators that GA is allowed to use.
	/// </summary>
	std::vector<PostGenerationOperator*>* postGenerationOperators_ = new std::vector<PostGenerationOperator*>();

	/// <summary>
	/// Evaluator instance that GA is to use.
	/// </summary>
	Evaluator* evaluator_ = nullptr;

	/// <summary>
	/// Current generation.
	/// </summary>
	unsigned int generation_ = 0;

	/// <summary>
	/// Separate generation tracker for checking the minimum generation criterion.
	/// </summary>
	unsigned int generationMin_ = 0;

	/// <summary>
	/// Elapsed time.
	/// </summary>
	long double time_ = 0;

	/// <summary>
	/// Integer code that determines why the algorithm was terminated prematurely.
	/// </summary>
	int terminationCode_ = -1;

	/// <summary>
	/// Collection of individuals that are the best of their generations.
	/// </summary>
	std::vector<Solution*>* bestSolutionHistory_ = new std::vector<Solution*>();

	/// <summary>
	/// Index that keeps track of the best overall individual.
	/// </summary>
	unsigned int bestSolutionTracker_ = 0;

};

