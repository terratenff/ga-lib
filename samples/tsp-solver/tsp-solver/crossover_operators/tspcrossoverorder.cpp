#include "tspcrossoverorder.h"
#include "../tspsolution.h"
#include <algorithm>
#include <iostream>
#include <string>

TSPCrossoverOrder::TSPCrossoverOrder(ProblemData* data, Evaluator* evaluator, unsigned int useWeight):
	CrossoverOperator(data, evaluator, useWeight)
{
}

std::pair<Solution*, Solution*> TSPCrossoverOrder::run(Solution* parent1, Solution* parent2, RNG* rng)
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

    unsigned int rand1Size = rng->rand() % parentC1.size();
    unsigned int rand2Size = rng->rand() % parentC2.size();
    unsigned int rand1InsertionPoint = rng->rand() % (parentC1.size() - rand1Size);
    unsigned int rand2InsertionPoint = rng->rand() % (parentC2.size() - rand2Size);
    std::vector<int> gene1, gene2;

    // Offspring 1.
    gene1 = std::vector<int>(parentC1.begin() + rand1InsertionPoint, parentC1.begin() + rand1InsertionPoint + rand1Size);
    for (unsigned int i = 0; i < parentC2.size(); i++)
    {
        int subject = parentC2[i];
        if (std::find(gene1.begin(), gene1.end(), subject) == gene1.end())
        {
            offspringC1.push_back(subject);
        }
    }
    if (offspringC1.size() < rand1InsertionPoint) offspringC1.insert(offspringC1.begin() + rand1InsertionPoint, gene1.begin(), gene1.end());
    else offspringC1.insert(offspringC1.end(), gene1.begin(), gene1.end());

    // Offspring 2.
    gene2 = std::vector<int>(parentC2.begin() + rand2InsertionPoint, parentC2.begin() + rand2InsertionPoint + rand2Size);
    for (unsigned int i = 0; i < parentC1.size(); i++)
    {
        int subject = parentC1[i];
        if (std::find(gene2.begin(), gene2.end(), subject) == gene2.end())
        {
            offspringC2.push_back(subject);
        }
    }
    if (offspringC2.size() < rand2InsertionPoint) offspringC2.insert(offspringC2.begin() + rand2InsertionPoint, gene2.begin(), gene2.end());
    else offspringC2.insert(offspringC2.end(), gene2.begin(), gene2.end());

	return pair;
}

void TSPCrossoverOrder::print()
{
	std::cout << "Order Crossover (Weight: " + std::to_string(getUseWeight()) + ")" << std::endl;
}
