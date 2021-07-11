#include "pch.h"
#include "terminationcriteria.h"

TerminationCriteria::TerminationCriteria(
	unsigned int generationMin,
	unsigned int generationMax,
	long double timeMin,
	long double timeMax,
	float fitnessMin,
	float fitnessMax) :
	generationMin_(generationMin),
	generationMax_(generationMax),
	timeMin_(timeMin),
	timeMax_(timeMax),
	fitnessMin_(fitnessMin),
	fitnessMax_(fitnessMax)
{
}

bool TerminationCriteria::checkGenerationMin(unsigned int generationMin)
{
	if (generationMin >= generationMin_) return true;
	else return false;
}

bool TerminationCriteria::checkGenerationMax(unsigned int generationMax)
{
	if (generationMax >= generationMax_) return true;
	else return false;
}

bool TerminationCriteria::checkTimeMin(long double timeMin)
{
	if (timeMin > timeMin_) return true;
	else return false;
}

bool TerminationCriteria::checkTimeMax(long double timeMax)
{
	if (timeMax > timeMax_) return true;
	else return false;
}

bool TerminationCriteria::checkFitness(float fitness)
{
	if (fitness > fitnessMax_ || fitness < fitnessMin_) return true;
	else return false;
}

const unsigned int TerminationCriteria::getGenerationMin() const
{
	return generationMin_;
}

const unsigned int TerminationCriteria::getGenerationMax() const
{
	return generationMax_;
}

const long double TerminationCriteria::getTimeMin() const
{
	return timeMin_;
}

const long double TerminationCriteria::getTimeMax() const
{
	return timeMax_;
}

const float TerminationCriteria::getFitnessMin() const
{
	return fitnessMin_;
}

const float TerminationCriteria::getFitnessMax() const
{
	return fitnessMax_;
}
