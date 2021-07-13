#pragma once

#include "problemdata.h"
#include "evaluator.h"
#include "population.h"

#ifdef GALIB_EXPORTS
#define POSTGENERATION_API __declspec(dllexport)
#else
#define POSTGENERATION_API __declspec(dllimport)
#endif

/// <summary>
/// Post-generation operator is an optional operation that is used on the new population once that has been created.
/// </summary>
class POSTGENERATION_API PostGenerationOperator
{
public:

	/// <summary>
	/// Creates a post-generation operator. It is expected to be created dynamically (raw pointer).
	/// </summary>
	/// <param name="data">Information related to the problem that is to be solved.</param>
	/// <param name="evaluator">Evaluator object that has been selected to evaluate population individuals.</param>
	/// <param name="generationFrequency">
	/// Determines how frequently the post-generation operator is to be used.
	/// For example, if it is set 100, it is used once every 100 generations.
	/// </param>
	PostGenerationOperator(ProblemData* data, Evaluator* evaluator, unsigned int generationFrequency);

	/// <summary>
	/// Getter for generation frequency.
	/// </summary>
	/// <returns>Generation frequency. Post-generation operator is used once every x generations.</returns>
	unsigned int getGenerationFrequency();

	/// <summary>
	/// The main function of the post-generation operator. New and old (current) population are taken
	/// and individual-wise changes are made to the new population.
	/// </summary>
	/// <param name="populationNew">The population that will replace the current population.</param>
	/// <param name="populationOld">The population that will be replaced by the new population.</param>
	virtual void run(Population* populationNew, Population* populationOld = nullptr) = 0;

	/// <summary>
	/// Designated print-function for the post-generation operator. This is expected to be contained in one line.
	/// </summary>
	virtual void print() = 0;
protected:
	
	/// <summary>
	/// Information related to the problem that is to be solved. This can be used to take constraints
	/// into account during the post-generation operation.
	/// </summary>
	ProblemData* data_;

	/// <summary>
	/// Evaluator object that has been selected to evaluate population individuals. This can be used to
	/// retry post-generation operations for better fitness values if that is deemed necessary.
	/// </summary>
	Evaluator* evaluator_;
private:

	/// <summary>
	/// Determines how frequently the post-generation operator should be used. It is the number x in
	/// "once every x generations".
	/// </summary>
	unsigned int generationFrequency_;
};

