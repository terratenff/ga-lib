#include "pch.h"
#include "rng.h"
#include <time.h>

RNG::RNG(int seed): seed_(seed)
{
	if (seed == 0) srand((unsigned int)time(0));
}

RNG::~RNG()
{
}

RNG* RNG::clone(int seed)
{
	return new RNG(seed);
}

unsigned int RNG::rand()
{
	return std::rand();
}
