#include "pch.h"
#include "rng.h"

RNG::RNG(unsigned int seed): rng_(new std::mt19937(seed))
{
}

RNG::~RNG()
{
	delete rng_;
}

unsigned int RNG::rand()
{
	return rng_->operator()();
}

std::mt19937* RNG::engine()
{
	return rng_;
}
