#pragma once

#ifdef GALIB_EXPORTS
#define TERMINATION_CRITERIA_API __declspec(dllexport)
#else
#define TERMINATION_CRITERIA_API __declspec(dllimport)
#endif

class TERMINATION_CRITERIA_API TerminationCriteria
{
public:
	TerminationCriteria(unsigned int generationMin, unsigned int generationMax, unsigned int timeMin, unsigned int timeMax, float fitnessMin, float fitnessMax);
	bool checkGenerationMin(unsigned int generationMin);
	bool checkGenerationMax(unsigned int generationMax);
	bool checkTimeMin(unsigned int timeMin);
	bool checkTimeMax(unsigned int timeMax);
	bool checkFitness(unsigned int fitness);
private:
	unsigned int generationMin_;
	unsigned int generationMax_;
	unsigned int timeMin_;
	unsigned int timeMax_;
	float fitnessMin_;
	float fitnessMax_;
};

