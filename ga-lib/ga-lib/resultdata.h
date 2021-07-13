#pragma once

#include "solution.h"
#include <string>

#ifdef GALIB_EXPORTS
#define RESULTDATA_API __declspec(dllexport)
#else
#define RESULTDATA_API __declspec(dllimport)
#endif

/// <summary>
/// Result data contains information about the best discovered solution and other
/// bits and pieces that relate to the algorithm's execution.
/// </summary>
class RESULTDATA_API ResultData
{
public:

	/// <summary>
	/// Creates the result data. All of the information in the parameters have to be
	/// collected from the GA instance after it has finished.
	/// </summary>
	/// <param name="solution">The best discovered solution.</param>
	/// <param name="time">Total time elapsed during the algorithm's execution.</param>
	/// <param name="generation">Total number of generations that have been iterated during the algorithm's execution.</param>
	/// <param name="terminationCode">Integer code that determines why the algorithm has been terminated prematurely.</param>
	ResultData(Solution* solution, long double time, int generation, int terminationCode = 0);

	/// <summary>
	/// Designated print-function for the result data.
	/// </summary>
	void print();

	/// <summary>
	/// Saves the results into a file.
	/// </summary>
	/// <param name="path">Location of the file where the results are saved.</param>
	void save(std::string path);
protected:

	/// <summary>
	/// Best discovered solution.
	/// </summary>
	Solution* solution_;
private:

	/// <summary>
	/// Collects solution information from the best discovered individual and makes it
	/// part of this instance. This does not need to be explicitly called.
	/// </summary>
	virtual void constructData() = 0;

	/// <summary>
	/// Prints the algorithmic results of the solution.
	/// </summary>
	void printAlgorithmData();

	/// <summary>
	/// Prints the results from the solution.
	/// </summary>
	void printSolutionData();

	/// <summary>
	/// Creates a string that contains algorithmic results in a presentable format.
	/// </summary>
	/// <returns>Readable results of algorithmic execution.</returns>
	std::string makeAlgorithmString();

	/// <summary>
	/// Creates a string that contains solution results in a presentable format.
	/// </summary>
	/// <returns>Readable results of the solution.</returns>
	virtual std::string makeSolutionString() = 0;

	/// <summary>
	/// Total time elapsed during the algorithm's execution.
	/// </summary>
	long double time_;

	/// <summary>
	/// Total number of generations that have been iterated during the algorithm's execution.
	/// </summary>
	int generation_;

	/// <summary>
	/// Integer code that determines why the algorithm has been terminated prematurely.
	/// </summary>
	int terminationCode_;

	/// <summary>
	/// Flag that determines whether the results have been made part of this instance yet.
	/// </summary>
	bool isDataConstructed_ = false;
};

