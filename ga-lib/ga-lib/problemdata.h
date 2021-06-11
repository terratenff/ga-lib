#pragma once

#ifdef GALIB_EXPORTS
#define PROBLEMDATA_API __declspec(dllexport)
#else
#define PROBLEMDATA_API __declspec(dllimport)
#endif

class PROBLEMDATA_API ProblemData
{
public:
	ProblemData();
	virtual void print() = 0;
};

