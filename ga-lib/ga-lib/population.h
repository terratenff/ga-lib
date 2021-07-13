#pragma once
#include "solution.h"

#ifdef GALIB_EXPORTS
#define GA_POPULATION_API __declspec(dllexport)
#else
#define GA_POPULATION_API __declspec(dllimport)
#endif

/// <summary>
/// Population is an instance that contains a fixed number of individuals that have solutions to the
/// specified problem.
/// </summary>
class GA_POPULATION_API Population
{
public:

	/// <summary>
	/// Creates an empty population. It is expected to be created dynamically (raw pointer).
	/// </summary>
	/// <param name="size">Amount of space allocated for the population, in terms of individuals.</param>
	Population(unsigned int size);
	~Population();

	/// <summary>
	/// Setter for the direction in which the population is sorted.
	/// </summary>
	/// <param name="reverse">true = highest to lowest. false = lowest to highest.</param>
	void setSortOrder(bool reverse);

	/// <summary>
	/// Getter for the sort order.
	/// </summary>
	/// <returns>true = highest to lowest. false = lowest to highest.</returns>
	bool getSortOrder();

	/// <summary>
	/// Adds an individual into the population.
	/// </summary>
	/// <param name="solution">Subject individual.</param>
	/// <param name="suppressException">
	/// Determines whether an exception should be thrown if an addition would exceed capacity.
	/// If set to true, an out_of_range is thrown. If false, subject individual will not be added.
	/// </param>
	void addSolution(Solution* solution, bool suppressException = false);

	/// <summary>
	/// Getter for an individual in the population.
	/// </summary>
	/// <param name="i">Index.</param>
	/// <returns>Population individual situated at specified index.</returns>
	Solution* getSolution(unsigned int i);

	/// <summary>
	/// Replaces an individual at a specified location in the population.
	/// </summary>
	/// <param name="i">Index.</param>
	/// <param name="solution">An individual that is to replace one situated at specified index.</param>
	/// <param name="deleteSolution">Determines whether replaced individual should be deallocated.</param>
	void replaceSolution(unsigned int i, Solution* solution, bool deleteSolution = true);

	/// <summary>
	/// Combines two populations into one. It should be noted that population sizes are not considered here.
	/// </summary>
	/// <param name="subPopulation">Population that is to merged into this population and then deallocated.</param>
	void mergePopulation(Population* subPopulation);

	/// <summary>
	/// Getter for the size of the population.
	/// </summary>
	/// <returns>Population size.</returns>
	const unsigned int size() const;

	/// <summary>
	/// Performs an assessment of the population. The following information are collected from the fitness values
	/// of population individuals: lowest value, highest value, average and variance.
	/// </summary>
	void assessment();

	/// <summary>
	/// Sorts the population with respect to fitness and penalty values.
	/// </summary>
	void sort();

	/// <summary>
	/// Deallocates every individual in the population. The pointers to them are also removed.
	/// </summary>
	void clear();

	/// <summary>
	/// Designated print-function for the population. Population size and other information (from "assessment")
	/// are displayed.
	/// </summary>
	virtual void print();
private:

	/// <summary>
	/// Collection of individuals.
	/// </summary>
	std::vector<Solution*>* population_;

	/// <summary>
	/// The direction in which population individuals are sorted. true = highest to lowest. false = lowest to highest.
	/// </summary>
	bool sortOrder_ = false;

	/// <summary>
	/// Lowest recorded fitness value of the population.
	/// </summary>
	float lowestFitness_;

	/// <summary>
	/// Highest recorded fitness value of the population.
	/// </summary>
	float highestFitness_;

	/// <summary>
	/// Average fitness value of the population.
	/// </summary>
	float averageFitness_;

	/// <summary>
	/// Fitness variance of the population.
	/// </summary>
	float varianceFitness_;
};

