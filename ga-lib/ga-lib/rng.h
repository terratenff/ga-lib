#pragma once

#include <random>

#ifdef GALIB_EXPORTS
#define GA_RNG_API __declspec(dllexport)
#else
#define GA_RNG_API __declspec(dllimport)
#endif

/// <summary>
/// Simple wrapper for a pseudo random number generator (mt19937).
/// </summary>
class GA_RNG_API RNG
{
public:

	/// <summary>
	/// Creates a random number generator. It is expected to be created dynamically (raw pointer).
	/// </summary>
	/// <param name="seed"></param>
	RNG(unsigned int seed);
	~RNG();

	/// <summary>
	/// Generates a random unsigned integer.
	/// </summary>
	/// <returns>Random unsigned integer.</returns>
	unsigned int rand();

	/// <summary>
	/// Getter for the random number generator. This should be used whenever container shuffling is involved.
	/// </summary>
	/// <returns>mt19937 random number generator.</returns>
	std::mt19937* engine();
private:

	/// <summary>
	/// Random number generator.
	/// </summary>
	std::mt19937* rng_;
};

