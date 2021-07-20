#include "tspevaluator.h"
#include "tspdata.h"
#include "tspsolution.h"
#include <iostream>

TSPEvaluator::TSPEvaluator(ProblemData* data): Evaluator(data)
{
}

float TSPEvaluator::evaluateFitness(Solution* solution)
{
    const std::vector<std::vector<float>>& matrix = static_cast<TSPData*>(data_)->getMatrix();
    std::vector<int>& chromosome = static_cast<TSPSolution*>(solution)->getChromosome();

    float fitness = 0.0f;
    for (unsigned int i = 1; i < chromosome.size(); i++)
    {
        int from = chromosome[i - 1];
        int to = chromosome[i];
        fitness += matrix[from][to];
    }
    fitness += matrix[chromosome[chromosome.size() - 1]][chromosome[0]];
    solution->setFitness(fitness);
    return fitness;
}

float TSPEvaluator::getPartialEvaluation(Solution* solution, unsigned int start, unsigned int finish)
{
    const std::vector<std::vector<float>>& matrix = static_cast<TSPData*>(data_)->getMatrix();
    std::vector<int>& chromosome = static_cast<TSPSolution*>(solution)->getChromosome();

    float fitness = 0.0f;
    for (unsigned int i = start + 1; i < finish; i++)
    {
        int from = chromosome[i - 1];
        int to = chromosome[i];
        fitness += matrix[from][to];
    }
    if (finish == chromosome.size() - 1) fitness += matrix[chromosome[finish]][chromosome[0]];
    return fitness;
}

void TSPEvaluator::print()
{
    std::cout << "Normal TSP Solution Evaluator" << std::endl;
}
