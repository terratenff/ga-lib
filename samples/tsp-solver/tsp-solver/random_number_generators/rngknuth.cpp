#include "rngknuth.h"

RNGKNUTH::RNGKNUTH(int seed) : RNG(seed), rng_(std::knuth_b(seed))
{
}

RNG* RNGKNUTH::clone(int seed)
{
	return new RNGKNUTH(seed);
}

unsigned int RNGKNUTH::rand()
{
	return rng_();
}

void RNGKNUTH::shuffle(std::vector<int>& vect, unsigned int start, unsigned int finish)
{
	std::shuffle(vect.begin() + start, vect.begin() + finish, rng_);
}
