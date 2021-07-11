#pragma once

#include <random>

#ifdef GALIB_EXPORTS
#define GA_RNG_API __declspec(dllexport)
#else
#define GA_RNG_API __declspec(dllimport)
#endif

class GA_RNG_API RNG
{
public:
	RNG(unsigned int seed);
	~RNG();
	unsigned int rand();
	std::mt19937* engine();
private:
	std::mt19937* rng_;
};

