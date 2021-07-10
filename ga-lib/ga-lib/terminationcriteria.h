#pragma once

#ifdef GALIB_EXPORTS
#define TERMINATION_CRITERIA_API __declspec(dllexport)
#else
#define TERMINATION_CRITERIA_API __declspec(dllimport)
#endif

class TERMINATION_CRITERIA_API TerminationCriteria
{
public:
	TerminationCriteria(unsigned int generationMin, unsigned int generationMax, long double timeMin, long double timeMax, float fitnessMin, float fitnessMax);
	bool checkGenerationMin(unsigned int generationMin);
	bool checkGenerationMax(unsigned int generationMax);
	bool checkTimeMin(long double timeMin);
	bool checkTimeMax(long double timeMax);
	bool checkFitness(float fitness);
	const unsigned int getGenerationMin() const;
	const unsigned int getGenerationMax() const;
	const long double getTimeMin() const;
	const long double getTimeMax() const;
	const float getFitnessMin() const;
	const float getFitnessMax() const;
private:
	const unsigned int generationMin_;
	const unsigned int generationMax_;
	const long double timeMin_;
	const long double timeMax_;
	const float fitnessMin_;
	const float fitnessMax_;
};

