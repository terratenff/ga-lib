#include "tspcrossoveronepoint.h"
#include "../tspsolution.h"
#include <iostream>
#include <string>

TSPCrossoverOnePoint::TSPCrossoverOnePoint(ProblemData* data, Evaluator* evaluator, unsigned int useWeight):
    CrossoverOperator(data, evaluator, useWeight)
{
}

std::pair<Solution*, Solution*> TSPCrossoverOnePoint::run(Solution* parent1, Solution* parent2, RNG* rng)
{
    const std::vector<int>& parentC1 = static_cast<TSPSolution*>(parent1)->getChromosome();
    const std::vector<int>& parentC2 = static_cast<TSPSolution*>(parent2)->getChromosome();
    TSPSolution* offspring1 = new TSPSolution();
    TSPSolution* offspring2 = new TSPSolution();
    std::pair<Solution*, Solution*> pair;
    pair.first = offspring1;
    pair.second = offspring2;

    std::vector<int>& offspringC1 = offspring1->getChromosome();
    std::vector<int>& offspringC2 = offspring2->getChromosome();
    offspringC1.reserve(parentC1.size());
    offspringC2.reserve(parentC2.size());
    unsigned int cutoffPoint = rng->rand() % parentC1.size();

    // Offspring 1.
    for (unsigned int i = 0; i < cutoffPoint; i++)
    {
        offspringC1.push_back(parentC1[i]);
    }
    for (unsigned int i = 0; i < parentC2.size(); i++)
    {
        int subject = parentC2[i];
        if (std::find(parentC1.begin(), parentC1.begin() + cutoffPoint, subject) == parentC1.begin() + cutoffPoint)
        {
            offspringC1.push_back(subject);
        }
    }

    // Offspring 2.
    for (unsigned int i = 0; i < parentC2.size(); i++)
    {
        int subject = parentC2[i];
        if (std::find(parentC1.begin() + cutoffPoint, parentC1.end(), subject) == parentC1.end())
        {
            offspringC2.push_back(subject);
        }
    }
    for (unsigned int i = cutoffPoint; i < parentC1.size(); i++)
    {
        offspringC2.push_back(parentC1[i]);
    }

    return pair;
}

void TSPCrossoverOnePoint::print()
{
    std::cout << "1-Point Crossover (Weight: " + std::to_string(getUseWeight()) + ")" << std::endl;
}
