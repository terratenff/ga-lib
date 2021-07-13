#pragma once

#include <vector>

#ifdef GALIB_EXPORTS
#define GA_SOLUTION_API __declspec(dllexport)
#else
#define GA_SOLUTION_API __declspec(dllimport)
#endif

/// <summary>
/// Solution (often called an "individual" in a population) is an entity that bears a solution
/// to the presented problem. The solution itself is referred to as a "chromosome" that
/// contains the specific information.
/// </summary>
class GA_SOLUTION_API Solution
{
public:

	/// <summary>
	/// Creates a solution. It is expected to be created dynamically (raw pointer).
	/// </summary>
	Solution();
	virtual ~Solution() = 0;
	bool operator<(Solution& other);
	bool operator>(Solution& other);
	bool operator==(Solution& other);

	/// <summary>
	/// Setter for the fitness value.
	/// </summary>
	/// <param name="var">Fitness.</param>
	void setFitness(float var);

	/// <summary>
	/// Setter for the penalty value.
	/// </summary>
	/// <param name="var">Penalty.</param>
	void setPenalty(float var);

	/// <summary>
	/// Getter for the fitness value.
	/// </summary>
	/// <returns>Solution fitness value.</returns>
	float getFitness();

	/// <summary>
	/// Getter for the penalty value.
	/// </summary>
	/// <returns>Solution penalty value.</returns>
	float getPenalty();

	/// <summary>
	/// Designated print-function for the solution.
	/// </summary>
	virtual void print() = 0;
private:

	/// <summary>
	/// Solution fitness value.
	/// </summary>
	float fitness_;

	/// <summary>
	/// Solution penalty value.
	/// </summary>
	float penalty_;
};
