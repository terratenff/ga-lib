#pragma once

#include "rng.h"
#include <random>

/// <summary>
/// Wrapper for the Mersenne Twister pseudo-random number generator.
/// Current dilemma: standard rand() outperforms mt19937 here.
/// </summary>
class RNGMT : public RNG
{
public:
	RNGMT(int seed);
	RNG* clone(int seed) override;
	unsigned int rand() override;

	/// <summary>
	/// Wrapper function for shuffling a container within the RNG instance.
	/// </summary>
	/// <param name="vect">Vector of integers. (TSP chromosome)</param>
	/// <param name="start">begin() + start</param>
	/// <param name="finish">begin() + finish</param>
	void shuffle(std::vector<int>& vect, unsigned int start, unsigned int finish);
private:
	std::mt19937 mt_;
	std::random_device rd_;
	std::uniform_int_distribution<> distribution_;
};