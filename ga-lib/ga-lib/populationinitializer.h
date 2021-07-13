#pragma once

#include "problemdata.h"
#include "evaluator.h"
#include "population.h"
#include "solution.h"

#ifdef GALIB_EXPORTS
#define INITIALIZER_API __declspec(dllexport)
#else
#define INITIALIZER_API __declspec(dllimport)
#endif

/// <summary>
/// Population Initializer is in charge of creating generation 0 population.
/// </summary>
class INITIALIZER_API PopulationInitializer
{
public:

	/// <summary>
	/// Creates a population initializer. It is expected to be created dynamically (raw pointer).
	/// </summary>
	/// <param name="data">Information related to the problem that is to be solved.</param>
	/// <param name="evaluator">Evaluator object that has been selected to evaluate population individuals.</param>
	/// <param name="useWeight">Weight value that ultimately determines the probability of the population initializer being used.</param>
	PopulationInitializer(ProblemData* data, Evaluator* evaluator, unsigned int useWeight);

	/// <summary>
	/// Simple getter for the population initializer's weight value.
	/// </summary>
	/// <returns>Weight value. Determines the probability of the population initializer being used.</returns>
	unsigned int getUseWeight();

	/// <summary>
	/// Creates a population of specified size. This is used only if there are no other
	/// population initializers specified.
	/// </summary>
	/// <param name="populationSize">Number of individuals that the population initializer has to make.</param>
	/// <returns>Population created by the population initializer.</returns>
	virtual Population* createPopulation(unsigned int populationSize) = 0;

	/// <summary>
	/// Creates an individual. This is used if more than one population initializer is specified.
	/// </summary>
	/// <returns>Solution created by the population initializer.</returns>
	virtual Solution* createSolution() = 0;

	/// <summary>
	/// Designated print-function for the population initializer. This is expected to be contained in one line.
	/// </summary>
	virtual void print() = 0;
protected:
	
	/// <summary>
	/// Information related to the problem that is to be solved. This can be used to take constraints
	/// into account during the population initialization.
	/// </summary>
	ProblemData* data_;

	/// <summary>
	/// Evaluator object that has been selected to evaluate population individuals. This can be used to
	/// retry individual creations for better fitness values if that is deemed necessary.
	/// </summary>
	Evaluator* evaluator_;
private:

	/// <summary>
	/// Weight value that ultimately determines the probability of the population initializer being used.
	/// This is determined between other population initializers.
	/// If the weight of the population initializer is 20, and total weight among all of them is 100,
	/// the probability of the population initializer being used is 20/100, i.e. 20%. If only one
	/// population initializer is given, then it is always used.
	/// The probability is rolled for every individual creation.
	/// </summary>
	unsigned int useWeight_;
};

