#include "pch.h"
#include "rng.h"
#include <time.h>

RNG::RNG(int seed): seed_(seed)
{
	srand((unsigned int)time(0) + seed);
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
