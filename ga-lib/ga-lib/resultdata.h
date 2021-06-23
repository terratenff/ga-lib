#pragma once

#include "solution.h"

#ifdef GALIB_EXPORTS
#define RESULTDATA_API __declspec(dllexport)
#else
#define RESULTDATA_API __declspec(dllimport)
#endif

class RESULTDATA_API ResultData
{
public:
	ResultData();
	virtual void constructData(Solution* solution) = 0;
	virtual void print() = 0;
	virtual void save() = 0;
};

