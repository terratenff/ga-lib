#include "pch.h"
#include "garunner.h"
#include <stdexcept>

GARunner::GARunner(int id, unsigned int subPopulationSize):
	id_(id),
	subPopulationSize_(subPopulationSize)
{
}

GARunner::~GARunner()
{
	delete subPopulation_;
	delete selectorWeights_;
	delete crossoverWeights_;
	delete mutationWeights_;
}

int GARunner::getId()
{
	return id_;
}

void GARunner::setReferencePopulation(Population* referencePopulation)
{
	referencePopulation_ = referencePopulation;
}

void GARunner::setSelectors(std::vector<Selector*>* selectors)
{
	selectors_ = selectors;
	unsigned int cumulativeWeight = 0;
	for (Selector* selector : *selectors)
	{
		cumulativeWeight += selector->getUseWeight();
		selectorWeights_->push_back(cumulativeWeight);
	}
	selectorTotal_ = cumulativeWeight;
}

void GARunner::setCrossoverOperators(std::vector<CrossoverOperator*>* crossoverOperators)
{
	crossoverOperators_ = crossoverOperators;
	unsigned int cumulativeWeight = 0;
	for (CrossoverOperator* crossoverOperator : *crossoverOperators)
	{
		cumulativeWeight += crossoverOperator->getUseWeight();
		crossoverWeights_->push_back(cumulativeWeight);
	}
	crossoverTotal_ = cumulativeWeight;
}

void GARunner::setMutationOperators(std::vector<MutationOperator*>* mutationOperators)
{
	mutationOperators_ = mutationOperators;
	unsigned int cumulativeWeight = 0;
	for (MutationOperator* mutationOperator : *mutationOperators)
	{
		cumulativeWeight += mutationOperator->getUseWeight();
		mutationWeights_->push_back(cumulativeWeight);
	}
	mutationTotal_ = cumulativeWeight;
}

void GARunner::setEvaluator(Evaluator* evaluator)
{
	evaluator_ = evaluator;
}

void GARunner::setSolutionTimeout(long double timeMin)
{
	timeMin_ = timeMin;
}

void GARunner::createSubPopulation()
{
	if (subPopulation_ != nullptr) delete subPopulation_;
	subPopulation_ = new Population(subPopulationSize_);

	for (unsigned int i = 0; i < subPopulationSize_; i+=2)
	{
		// 1. Use random selectors to find parent candidates.
		unsigned int selectedIndex1 = 0;
		unsigned int selectedIndex2 = 0;
		unsigned int weight1 = rand() % (selectorTotal_ + 1);
		unsigned int weight2 = rand() % (selectorTotal_ + 1);
		bool selected1 = false;
		bool selected2 = false;
		for (unsigned int j = 0; j < selectors_->size(); j++)
		{
			if (selectorWeights_->operator[](j) < weight1)
			{
				selectedIndex1 = j;
				selected1 = true;
			}
			if (selectorWeights_->operator[](j) < weight2)
			{
				selectedIndex2 = j;
				selected2 = true;
			}
			if (selected1 && selected2) break;
		}

		Solution* parent1 = selectors_->operator[](selectedIndex1)->select(referencePopulation_);
		Solution* parent2 = selectors_->operator[](selectedIndex2)->select(referencePopulation_);

		// 2. Apply a random crossover operator. Utilize operator weights.
		selectedIndex1 = 0;
		selectedIndex2 = 0;
		weight1 = rand() % (crossoverTotal_ + 1);
		weight2 = rand() % (crossoverTotal_ + 1);
		selected1 = false;
		selected2 = false;
		for (unsigned int j = 0; j < crossoverOperators_->size(); j++)
		{
			if (crossoverWeights_->operator[](j) < weight1)
			{
				selectedIndex1 = j;
				selected1 = true;
			}
			if (crossoverWeights_->operator[](j) < weight2)
			{
				selectedIndex2 = j;
				selected2 = true;
			}
			if (selected1 && selected2) break;
		}

		std::pair<Solution*, Solution*> offspringPair = crossoverOperators_->operator[](selectedIndex1)->run(parent1, parent2);
		Solution* offspring1 = offspringPair.first;
		Solution* offspring2 = offspringPair.second;

		// 3. Apply a random mutation operator. Utilize operator weights.
		selectedIndex1 = 0;
		selectedIndex2 = 0;
		weight1 = rand() % (mutationTotal_ + 1);
		weight2 = rand() % (mutationTotal_ + 1);
		selected1 = false;
		selected2 = false;
		for (unsigned int j = 0; j < mutationOperators_->size(); j++)
		{
			if (mutationWeights_->operator[](j) < weight1)
			{
				selectedIndex1 = j;
				selected1 = true;
			}
			if (mutationWeights_->operator[](j) < weight2)
			{
				selectedIndex2 = j;
				selected2 = true;
			}
			if (selected1 && selected2) break;
		}

		mutationOperators_->operator[](selectedIndex1)->run(offspring1);
		mutationOperators_->operator[](selectedIndex1)->run(offspring2);

		// 4. Apply the final evaluation.
		evaluator_->evaluateFitness(offspring1);
		evaluator_->evaluatePenalty(offspring1);
		evaluator_->evaluateFitness(offspring2);
		evaluator_->evaluatePenalty(offspring2);

		// 5. Push to subPopulation_.
		subPopulation_->addSolution(offspring1);
		subPopulation_->addSolution(offspring2, true);
	}

	referencePopulation_ = nullptr;
}

Population* GARunner::getSubPopulation()
{
	return subPopulation_;
}

void GARunner::run()
{
	throw std::exception("GARunner::run() is reserved for multi-threaded implementations.");
}

void GARunner::terminate()
{
	throw std::exception("GARunner::terminate() is reserved for multi-threaded implementations.");
}

void GARunner::threadFunction()
{
	throw std::exception("GARunner::threadFunction() is reserved for multi-threaded implementations.");
}

