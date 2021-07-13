#pragma once

#include "solution.h"
#include "problemdata.h"
#include "evaluator.h"
#include "rng.h"

#ifdef GALIB_EXPORTS
#define CROSSOVER_API __declspec(dllexport)
#else
#define CROSSOVER_API __declspec(dllimport)
#endif

/// <summary>
/// The crossover operator takes two population individuals that have been selected to operate as parents.
/// Chromosomes of the parents are mixed with each other to create offspring.
/// If the implementation attempts to perform the crossover multiple times, it is recommended to
/// give the crossover operator a limited number of attempts, after which it gives up.
/// </summary>
class CROSSOVER_API CrossoverOperator
{
public:

	/// <summary>
	/// Creates a crossover operator. It is expected to be created dynamically (raw pointer).
	/// </summary>
	/// <param name="data">Information related to the problem that is to be solved.</param>
	/// <param name="evaluator">Evaluator object that has been selected to evaluate population individuals.</param>
	/// <param name="useWeight">Weight value that ultimately determines the probability of the crossover operator being used.</param>
	CrossoverOperator(ProblemData* data, Evaluator* evaluator, unsigned int useWeight);

	/// <summary>
	/// Simple getter for the crossover operator's weight value.
	/// </summary>
	/// <returns>Weight value. Determines the probability of the crossover operator being used.</returns>
	unsigned int getUseWeight();

	/// <summary>
	/// The main function of the crossover operator. Two population individuals share their chromosomes
	/// to create new ones that are given to new individuals. These are the offspring of the selected individuals.
	/// </summary>
	/// <param name="parent1">Population individual that has been given the role of Parent 1.</param>
	/// <param name="parent2">Population individual that has been given the role of Parent 2.</param>
	/// <param name="rng">
	/// Random Number Generator instance. This should be used whenever random operations are involved
	/// (especially if multithreading is implemented).
	/// </param>
	/// <returns>Two offspring that have been created from their parents.</returns>
	virtual std::pair<Solution*, Solution*> run(Solution* parent1, Solution* parent2, RNG* rng) = 0;

	/// <summary>
	/// Designated print-function for the crossover operator. This is expected to be contained in one line.
	/// </summary>
	virtual void print() = 0;
protected:

	/// <summary>
	/// Information related to the problem that is to be solved. This can be used to take constraints
	/// into account during the crossover operation.
	/// </summary>
	ProblemData* data_;

	/// <summary>
	/// Evaluator object that has been selected to evaluate population individuals. This can be used to
	/// retry crossover operations for better fitness values if that is deemed necessary.
	/// </summary>
	Evaluator* evaluator_;
private:

	/// <summary>
	/// Weight value that ultimately determines the probability of the crossover operator being used.
	/// This is determined between other crossover operators.
	/// If the weight of the crossover operator is 20, and total weight among all of them is 100,
	/// the probability of the crossover operator being used is 20/100, i.e. 20%. If only one
	/// crossover operator is given, then it is always used.
	/// </summary>
	unsigned int useWeight_;
};

