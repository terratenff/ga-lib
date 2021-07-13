#pragma once

#include "population.h"
#include "solution.h"
#include "rng.h"

#ifdef GALIB_EXPORTS
#define SELECTOR_API __declspec(dllexport)
#else
#define SELECTOR_API __declspec(dllimport)
#endif

/// <summary>
/// Selectors decide which individuals in the current population act as parents for the crossover operation.
/// </summary>
class SELECTOR_API Selector
{
public:

	/// <summary>
	/// Creates a selector. It is expected to be created dynamically (raw pointer).
	/// </summary>
	/// <param name="candidateCount">Number of individuals that are selected at random to compete in the selection.</param>
	/// <param name="useWeight">Weight value that ultimately determines the probability of the selector being used.</param>
	Selector(unsigned int candidateCount, unsigned int useWeight);

	/// <summary>
	/// Simple getter for the selector's weight value.
	/// </summary>
	/// <returns>Weight value. Determines the probability of the selector being used.</returns>
	unsigned int getUseWeight();

	/// <summary>
	/// The main function of the selector. Individuals are taken at random from the specified
	/// population, and one of the individuals becomes a parent.
	/// </summary>
	/// <param name="population">The population where individuals are taken. This is expected to be the current population.</param>
	/// <param name="rng">
	/// Random Number Generator instance. This should be used whenever random operations are involved
	/// (especially if multithreading is implemented).
	/// </param>
	/// <returns>The individual that has been selected to be a parent.</returns>
	virtual Solution* select(Population* population, RNG* rng) = 0;

	/// <summary>
	/// Designated print-function for the selector. This is expected to be contained in one line.
	/// </summary>
	virtual void print() = 0;
protected:

	/// <summary>
	/// The number of individuals that are picked at random to compete in being selected
	/// as a parent.
	/// </summary>
	unsigned int candidateCount_;
private:

	/// <summary>
	/// Weight value that ultimately determines the probability of the selector being used.
	/// This is determined between other selectors.
	/// If the weight of the selector is 20, and total weight among all of them is 100,
	/// the probability of the selector being used is 20/100, i.e. 20%. If only one
	/// selector is given, then it is always used.
	/// </summary>
	unsigned int useWeight_;
};

