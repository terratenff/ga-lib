#pragma once

#include <random>

#ifdef GALIB_EXPORTS
#define GA_RNG_API __declspec(dllexport)
#else
#define GA_RNG_API __declspec(dllimport)
#endif

/// <summary>
/// Simple wrapper for a pseudo random number generator. Uses "std::rand" Inherit this class to use different
/// random number generators: "std::rand" is not recommended for multithreaded implementations.
/// </summary>
class GA_RNG_API RNG
{
public:

	/// <summary>
	/// Creates a random number generator. It is expected to be created dynamically (raw pointer).
	/// </summary>
	RNG(int seed);
	~RNG();

	/// <summary>
	/// Createa an identical copy (except for the seed) of the random number generator.
	/// </summary>
	/// <param name="seed">Seed of the copy.</param>
	/// <returns>Copy of this pseudo random number generator.</returns>
	virtual RNG* clone(int seed);

	/// <summary>
	/// Generates a random unsigned integer.
	/// </summary>
	/// <returns>Random unsigned integer.</returns>
	virtual unsigned int rand();
private:
	int seed_;
};

