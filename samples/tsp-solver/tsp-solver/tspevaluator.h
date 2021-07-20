#pragma once

#include "evaluator.h"
#include "problemdata.h"
#include "solution.h"

/// <summary>
/// Evaluator designed for the normal TSP. Elements are "visited" in a sequential fashion. Once the last element
/// has been reached, a return trip is made to the first element.
/// </summary>
class TSPEvaluator: public Evaluator
{
public:
	TSPEvaluator(ProblemData* data);
	float evaluateFitness(Solution* solution) override;

	/// <summary>
	/// Performs a partial evaluation of the solution. If the last element is referenced,
	/// the return trip is also considered.
	/// </summary>
	/// <param name="solution">Solution subject to partial evaluation.</param>
	/// <param name="start">Start index.</param>
	/// <param name="finish">Destination index.</param>
	/// <returns>Fitness value from specified start to finish.</returns>
	float getPartialEvaluation(Solution* solution, unsigned int start, unsigned int finish);
	void print() override;
};

