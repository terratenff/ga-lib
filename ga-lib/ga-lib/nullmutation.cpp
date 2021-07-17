#include "pch.h"
#include "nullmutation.h"
#include <iostream>
#include <string>

NullMutation::NullMutation(ProblemData* data, Evaluator* evaluator, unsigned int useWeight):
	MutationOperator(data, evaluator, useWeight)
{
}

void NullMutation::run(Solution* offspring, RNG* rng)
{
}

void NullMutation::print()
{
	std::string text = "No Mutation (Weight: " + std::to_string(getUseWeight()) + ")";
	std::cout << text << std::endl;
}
