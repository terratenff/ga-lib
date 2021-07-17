#pragma once

#include "mutationoperator.h"

#ifdef GALIB_EXPORTS
#define NULL_MUTATION_API __declspec(dllexport)
#else
#define NULL_MUTATION_API __declspec(dllimport)
#endif

/// <summary>
/// This mutation operator can be used to skip the mutation operation.
/// </summary>
class NULL_MUTATION_API NullMutation :
    public MutationOperator
{
public:

    /// <summary>
    /// Creates a null mutation operator. It is expected to be created dynamically (raw pointer).
    /// </summary>
    /// <param name="data">Information related to the problem that is to be solved.</param>
	/// <param name="evaluator">Evaluator object that has been selected to evaluate population individuals.</param>
	/// <param name="useWeight">Weight value that ultimately determines the probability of the mutation operator being used.</param>
    NullMutation(ProblemData* data, Evaluator* evaluator, unsigned int useWeight);

    /// <summary>
    /// The main function of the mutation operator. Since the mutation operation is skipped,
    /// nothing is done.
    /// </summary>
    /// <param name="offspring">An individual that was created via crossover.</param>
    /// <param name="rng">
    /// Random Number Generator instance.
    /// </param>
    void run(Solution* offspring, RNG* rng) override;

    /// <summary>
    /// Designated print-function for the mutation operator. Prints the following:
    /// "No Mutation (Weight: X)", where X is the use weight.
    /// </summary>
    void print() override;
};

