#pragma once

#include "problemdata.h"
#include "solution.h"

#ifdef GALIB_EXPORTS
#define EVALUATOR_API __declspec(dllexport)
#else
#define EVALUATOR_API __declspec(dllimport)
#endif

/// <summary>
/// An evaluator takes a population individual and calculates its fitness value (and penalties if constraints are present)
/// from its chromosome using provided problem data as reference.
/// Fitness represents the feasibility of the population individual. Penalties are a result of constraint violations.
/// </summary>
class EVALUATOR_API Evaluator
{
public:

	/// <summary>
	/// Creates an evaluator. It is expected to be created dynamically (raw pointer).
	/// </summary>
	/// <param name="data">Information related to the problem that is to be solved.</param>
	Evaluator(ProblemData* data);

	/// <summary>
	/// Evaluates the fitness value of specified population individual.
	/// It is expected to both set the fitness value for the population individual and return the fitness value itself.
	/// </summary>
	/// <param name="solution">Population individual that is to be evaluated.</param>
	/// <returns>Fitness value of the evaluated individual.</returns>
	virtual float evaluateFitness(Solution* solution) = 0;

	/// <summary>
	/// Evaluates the total penalty value of specified population individual.
	/// It is expected to both set the penalty value for the population individual and return the penalty value itself.
	/// This function is purely optional, and only returns 0 if not overridden.
	/// </summary>
	/// <param name="solution">Population individual that is to be evaluated.</param>
	/// <returns>Penalty value of the evaluated individual.</returns>
	virtual float evaluatePenalty(Solution* solution);

	/// <summary>
	/// Designated print-function for the evaluator. This is expected to be contained in one line.
	/// </summary>
	virtual void print() = 0;
protected:

	/// <summary>
	/// Information related to the problem that is to be solved. This can be used to take constraints
	/// into account during the evaluation.
	/// </summary>
	ProblemData* data_;
};

