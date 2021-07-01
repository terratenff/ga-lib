#pragma once

#include "solution.h"
#include <string>

#ifdef GALIB_EXPORTS
#define RESULTDATA_API __declspec(dllexport)
#else
#define RESULTDATA_API __declspec(dllimport)
#endif

class RESULTDATA_API ResultData
{
public:
	ResultData(Solution* solution, long double time, int generation, int terminationCode = 0);
	void print();
	void save(std::string path);
protected:
	Solution* solution_;
private:
	virtual void constructData() = 0;
	void printAlgorithmData();
	void printSolutionData();
	std::string makeAlgorithmString();
	virtual std::string makeSolutionString() = 0;
	long double time_;
	int generation_;
	int terminationCode_;
	bool isDataConstructed_ = false;
};

