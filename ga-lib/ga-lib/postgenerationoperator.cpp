#include "pch.h"
#include "postgenerationoperator.h"

PostGenerationOperator::PostGenerationOperator(ProblemData* data, Evaluator* evaluator, unsigned int generationFrequency):
	data_(data),
	evaluator_(evaluator),
	generationFrequency_(generationFrequency)
{
}

void PostGenerationOperator::setupBestSolutionTracking(std::vector<Solution*>* bestSolutionHistory, unsigned int* bestSolutionTracker)
{
	bestSolutionHistory_ = bestSolutionHistory;
	bestSolutionTracker_ = bestSolutionTracker;
}

unsigned int PostGenerationOperator::getGenerationFrequency()
{
	return generationFrequency_;
}

Solution* PostGenerationOperator::getFromSolutionHistory(unsigned int i)
{
	return bestSolutionHistory_->operator[](i);
}

Solution* PostGenerationOperator::getBestSolution()
{
	return bestSolutionHistory_->operator[](*bestSolutionTracker_);
}

unsigned int PostGenerationOperator::getHistorySize()
{
	return bestSolutionHistory_->size();
}
