#pragma once

#include "crossoveroperator.h"

#ifdef GALIB_EXPORTS
#define NULL_CROSSOVER_API __declspec(dllexport)
#else
#define NULL_CROSSOVER_API __declspec(dllimport)
#endif

/// <summary>
/// This crossover operator can be used to skip the crossover operation.
/// </summary>
class NULL_CROSSOVER_API NullCrossover :
    public CrossoverOperator
{
public:

    /// <summary>
    /// Creates a null crossover operator. It is expected to be created dynamically (raw pointer).
    /// </summary>
    /// <param name="data">Information related to the problem that is to be solved.</param>
    /// <param name="evaluator">Evaluator object that has been selected to evaluate population individuals.</param>
    /// <param name="useWeight">Weight value that ultimately determines the probability of the crossover operator being used.</param>
    NullCrossover(ProblemData* data, Evaluator* evaluator, unsigned int useWeight);

	/// <summary>
	/// The main function of the crossover operator. Since the crossover operation is skipped, the parents
	/// become the offspring.
	/// </summary>
	/// <param name="parent1">Population individual that has been given the role of Parent 1.</param>
	/// <param name="parent2">Population individual that has been given the role of Parent 2.</param>
	/// <param name="rng">
	/// Random Number Generator instance.
	/// </param>
	/// <returns>Deep copies of the parents.</returns>
    std::pair<Solution*, Solution*> run(Solution* parent1, Solution* parent2, RNG* rng) override;

    /// <summary>
    /// Designated print-function for the crossover operator. Prints the following:
    /// "No Crossover (Weight: X)", where X is the use weight.
    /// </summary>
    void print() override;
};

