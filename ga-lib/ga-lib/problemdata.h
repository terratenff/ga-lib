#pragma once

#ifdef GALIB_EXPORTS
#define PROBLEMDATA_API __declspec(dllexport)
#else
#define PROBLEMDATA_API __declspec(dllimport)
#endif

/// <summary>
/// Problem data is to contain information relevant to the problem that is to be solved.
/// </summary>
class PROBLEMDATA_API ProblemData
{
public:

	/// <summary>
	/// Creates the problem data. It is expected to be created dynamically (raw pointer).
	/// </summary>
	ProblemData();

	/// <summary>
	/// Designated print-function for the problem data.
	/// </summary>
	virtual void print() = 0;
};

