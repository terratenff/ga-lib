#pragma once

#include "population.h"
#include "solution.h"

#ifdef GALIB_EXPORTS
#define SELECTOR_API __declspec(dllexport)
#else
#define SELECTOR_API __declspec(dllimport)
#endif

class SELECTOR_API Selector
{
public:
	Selector(unsigned int useWeight);
	virtual Solution* select(Population* population) = 0;
private:
	unsigned int useWeight_;
};

