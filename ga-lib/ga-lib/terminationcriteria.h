#pragma once

#ifdef GALIB_EXPORTS
#define TERMINATION_CRITERIA_API __declspec(dllexport)
#else
#define TERMINATION_CRITERIA_API __declspec(dllimport)
#endif

/// <summary>
/// Termination criteria is a collection of conditions that are used to decide whether
/// the algorithm should be terminated prematurely.
/// </summary>
class TERMINATION_CRITERIA_API TerminationCriteria
{
public:

	/// <summary>
	/// Creates an instance of termination criteria. It is expected to be created dynamically (raw pointer).
	/// </summary>
	/// <param name="generationMin">Minimum generation. If the best overall individual does not improve within this many generations, the algorithm will be terminated.</param>
	/// <param name="generationMax">Maximum generation. After this many generations pass by, the algorithm will be terminated.</param>
	/// <param name="timeMin">Minimum time. If an individual cannot be created in this amount of time, the algorithm will be terminated.</param>
	/// <param name="timeMax">Maximum time. After this much time has elapsed, the algorithm will be terminated.</param>
	/// <param name="fitnessMin">Minimum fitness. If the fitness of the best overall individual is lower than this, the algorithm will be terminated.</param>
	/// <param name="fitnessMax">Maximum fitness. If the fitness of the best overall individual is higher than this, the algorithm will be terminated.</param>
	TerminationCriteria(unsigned int generationMin, unsigned int generationMax, long double timeMin, long double timeMax, float fitnessMin, float fitnessMax);

	/// <summary>
	/// Compares minimum generation criterion with current minimum generation tracker to see if the algorithm should be terminated.
	/// </summary>
	/// <param name="generationMin">Current minimum generation count.</param>
	/// <returns>true, if termination criterion is met. false otherwise.</returns>
	bool checkGenerationMin(unsigned int generationMin);

	/// <summary>
	/// Compares maximum generation criterion with current generation count to see if the algorithm should be terminated.
	/// </summary>
	/// <param name="generationMax">Current generation count.</param>
	/// <returns>true, if termination criterion is met. false otherwise.</returns>
	bool checkGenerationMax(unsigned int generationMax);

	/// <summary>
	/// Compares minimum time criterion with current individual creation time to see if the algorithm should be terminated.
	/// </summary>
	/// <param name="timeMin">Current individual creation time.</param>
	/// <returns>true, if termination criterion is met. false otherwise.</returns>
	bool checkTimeMin(long double timeMin);

	/// <summary>
	/// Compares maximum time criterion with current execution time to see if the algorithm should be terminated.
	/// </summary>
	/// <param name="timeMax">Current execution time.</param>
	/// <returns>true, if termination criterion is met. false otherwise.</returns>
	bool checkTimeMax(long double timeMax);

	/// <summary>
	/// Compares fitness criteria with the fitness value of the best discovered individual to see if
	/// the algorithm should be terminated.
	/// </summary>
	/// <param name="fitness">Fitness value of the current best discovered individual.</param>
	/// <returns>true, if termination criterion is met. false otherwise.</returns>
	bool checkFitness(float fitness);

	/// <summary>
	/// Getter for minimum generation criterion.
	/// </summary>
	/// <returns>Minimum generation criterion.</returns>
	const unsigned int getGenerationMin() const;

	/// <summary>
	/// Getter for maximum generation criterion.
	/// </summary>
	/// <returns>Maximum generation criterion.</returns>
	const unsigned int getGenerationMax() const;

	/// <summary>
	/// Getter for minimum time criterion.
	/// </summary>
	/// <returns>Minimum time criterion.</returns>
	const long double getTimeMin() const;

	/// <summary>
	/// Getter for maximum time criterion.
	/// </summary>
	/// <returns>Maximum time criterion.</returns>
	const long double getTimeMax() const;

	/// <summary>
	/// Getter for minimum fitness criterion.
	/// </summary>
	/// <returns>Minimum fitness criterion.</returns>
	const float getFitnessMin() const;

	/// <summary>
	/// Getter for maximum fitness criterion.
	/// </summary>
	/// <returns>Maximum fitness criterion.</returns>
	const float getFitnessMax() const;
private:

	/// <summary>
	/// Minimum generation criterion. Number of generations without the best discovered individual improving.
	/// </summary>
	const unsigned int generationMin_;

	/// <summary>
	/// Maximum generation criterion. Total number of generations allocated for the algorithm.
	/// </summary>
	const unsigned int generationMax_;

	/// <summary>
	/// Minimum time criterion. Total amount of time allocated for the creation of a single individual.
	/// </summary>
	const long double timeMin_;

	/// <summary>
	/// Maximum time criterion. Total amount of time allocated for the algorithm.
	/// </summary>
	const long double timeMax_;

	/// <summary>
	/// Minimum fitness criterion. Relevant in minimization problems.
	/// </summary>
	const float fitnessMin_;

	/// <summary>
	/// Maximum fitness criterion. Relevant in maximization problems.
	/// </summary>
	const float fitnessMax_;
};

