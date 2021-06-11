#include "pch.h"
#include "terminationcriteria.h"

TerminationCriteria::TerminationCriteria(
	unsigned int generationMin,
	unsigned int generationMax,
	unsigned int timeMin,
	unsigned int timeMax,
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
	if (generationMin > generationMin_) return true;
	else return false;
}

bool TerminationCriteria::checkGenerationMax(unsigned int generationMax)
{
	if (generationMax > generationMax_) return true;
	else return false;
}

bool TerminationCriteria::checkTimeMin(unsigned int timeMin)
{
	if (timeMin > timeMin_) return true;
	else return false;
}

bool TerminationCriteria::checkTimeMax(unsigned int timeMax)
{
	if (timeMax_ > timeMax_) return true;
	else return false;
}

bool TerminationCriteria::checkFitness(unsigned int fitness)
{
	if (fitness > fitnessMax_ || fitness < fitnessMin_) return true;
	else return false;
}
