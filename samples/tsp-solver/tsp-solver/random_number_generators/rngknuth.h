#pragma once

#include "rng.h"
#include <random>

/// <summary>
/// Wrapper for the Knuth-B pseudo-random number generator.
/// Current dilemma: standard rand() outperforms knuth_b here.
/// </summary>
class RNGKNUTH : public RNG
{
public:
	RNGKNUTH(int seed);
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
	std::knuth_b rng_;
};