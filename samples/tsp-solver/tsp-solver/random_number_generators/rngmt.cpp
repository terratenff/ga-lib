#include "rngmt.h"

RNGMT::RNGMT(int seed) : RNG(seed)
{
	mt_ = std::mt19937(rd_());
	distribution_ = std::uniform_int_distribution<>(0, 100000);
}

RNG* RNGMT::clone(int seed)
{
	return new RNGMT(seed);
}

unsigned int RNGMT::rand()
{
	return distribution_(mt_);
}

void RNGMT::shuffle(std::vector<int>& vect, unsigned int start, unsigned int finish)
{
	std::shuffle(vect.begin() + start, vect.begin() + finish, mt_);
}
