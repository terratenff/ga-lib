#include "tspmutationnearestneighbor.h"
#include "../tspsolution.h"
#include "../tspevaluator.h"
#include "../tspdata.h"
#include <iostream>
#include <string>

TSPMutationNearestNeighbor::TSPMutationNearestNeighbor(ProblemData* data, Evaluator* evaluator, unsigned int useWeight):
	MutationOperator(data, evaluator, useWeight)
{
}

void TSPMutationNearestNeighbor::run(Solution* offspring, RNG* rng)
{
	std::vector<int>& chromosome = static_cast<TSPSolution*>(offspring)->getChromosome();
	int rand1 = rng->rand() % chromosome.size();
	int rand2 = rng->rand() % chromosome.size();
	std::vector<int> gene;
	unsigned int insertionPoint;
	if (rand1 < rand2)
	{
		insertionPoint = rand1;
		gene = std::vector<int>(chromosome.begin() + rand1, chromosome.begin() + rand2);
	}
	else if (rand1 > rand2)
	{
		insertionPoint = rand2;
		gene = std::vector<int>(chromosome.begin() + rand2, chromosome.begin() + rand1);
	}
	else
	{
		insertionPoint = 0;
		gene = std::vector<int>(chromosome.begin(), chromosome.begin());
	}

	const std::vector<std::vector<float>>& matrix = static_cast<TSPData*>(data_)->getMatrix();
	unsigned int startIndex = 0;
	unsigned int geneSize = gene.size();
	for (unsigned int i = 1; i < geneSize; i++)
	{
		const std::vector<float>& vect = matrix[gene[startIndex]];
		gene.erase(gene.begin() + startIndex);
		std::vector<float> tempVect;
		std::vector<unsigned int> tempVectIndices;
		for (unsigned int j = 0; j < gene.size(); j++)
		{
			tempVect.push_back(vect[gene[j]]);
			tempVectIndices.push_back(gene[j]);
		}
		std::vector<float>::iterator iter = std::min_element(tempVect.begin(), tempVect.end());
		int targetIndex = unsigned int(std::distance(tempVect.begin(), iter));
		chromosome[insertionPoint + i] = tempVectIndices[targetIndex];
		startIndex = targetIndex;
	}
}

void TSPMutationNearestNeighbor::print()
{
	std::cout << "Nearest Neighbor (Weight: " + std::to_string(getUseWeight()) + ")" << std::endl;
}
