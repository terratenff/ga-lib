#pragma once

#include "solution.h"
#include "problemdata.h"
#include "evaluator.h"
#include "rng.h"

#ifdef GALIB_EXPORTS
#define MUTATION_API __declspec(dllexport)
#else
#define MUTATION_API __declspec(dllimport)
#endif

/// <summary>
/// The mutation operator takes a population individual that was created as a result of the crossover operation.
/// Its chromosome is taken and modified slightly in an effort to improve population diversity.
/// If the implementation attempts to perform the mutation multiple times, it is recommended to
/// give the mutation operator a limited number of attempts, after which it gives up.
/// </summary>
class MUTATION_API MutationOperator
{
public:

	/// <summary>
	/// Creates a mutation operator. It is expected to be created dynamically (raw pointer).
	/// </summary>
	/// <param name="data">Information related to the problem that is to be solved.</param>
	/// <param name="evaluator">Evaluator object that has been selected to evaluate population individuals.</param>
	/// <param name="useWeight">Weight value that ultimately determines the probability of the mutation operator being used.</param>
	MutationOperator(ProblemData* data, Evaluator* evaluator, unsigned int useWeight);

	/// <summary>
	/// Simple getter for the mutation operator's weight value.
	/// </summary>
	/// <returns>Weight value. Determines the probability of the mutation operator being used.</returns>
	unsigned int getUseWeight();

	/// <summary>
	/// The main function of the mutation operator. One population individual's chromosome is
	/// modified slightly. The individual is expected to be offspring.
	/// </summary>
	/// <param name="offspring">An individual that was created via crossover.</param>
	/// <param name="rng">
	/// Random Number Generator instance. This should be used whenever random operations are involved
	/// (especially if multithreading is implemented).
	/// </param>
	virtual void run(Solution* offspring, RNG* rng) = 0;

	/// <summary>
	/// Designated print-function for the mutation operator. This is expected to be contained in one line.
	/// </summary>
	virtual void print() = 0;
protected:

	/// <summary>
	/// Information related to the problem that is to be solved. This can be used to take constraints
	/// into account during the mutation operation.
	/// </summary>
	ProblemData* data_;

	/// <summary>
	/// Evaluator object that has been selected to evaluate population individuals. This can be used to
	/// retry mutation operations for better fitness values if that is deemed necessary.
	/// </summary>
	Evaluator* evaluator_;
private:

	/// <summary>
	/// Weight value that ultimately determines the probability of the mutation operator being used.
	/// This is determined between other mutation operators.
	/// If the weight of the mutation operator is 20, and total weight among all of them is 100,
	/// the probability of the mutation operator being used is 20/100, i.e. 20%. If only one
	/// mutation operator is given, then it is always used.
	/// </summary>
	unsigned int useWeight_;
};

