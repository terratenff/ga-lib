#include "pch.h"
#include "garunner.h"
#include <chrono>

GARunner::GARunner(int id, unsigned int subPopulationSize):
	id_(id),
	subPopulationSize_(subPopulationSize),
	rng_(new RNG(id))
{
}

GARunner::~GARunner()
{
	if (subPopulation_ != nullptr) delete subPopulation_;
	delete selectorWeights_;
	delete crossoverWeights_;
	delete mutationWeights_;
	delete rng_;
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

void GARunner::setRandomNumberGenerator(RNG* rng)
{
	rng_ = rng;
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
		std::chrono::steady_clock::time_point clockStart = std::chrono::steady_clock::now();

		// 1. Use random selectors to find parent candidates.
		unsigned int selectedIndex1 = 0;
		unsigned int selectedIndex2 = 0;
		unsigned int weight1 = rng_->rand() % (selectorTotal_ + 1);
		unsigned int weight2 = rng_->rand() % (selectorTotal_ + 1);
		bool selected1 = false;
		bool selected2 = false;
		for (unsigned int j = 0; j < selectors_->size(); j++)
		{
			if (weight1 < selectorWeights_->operator[](j))
			{
				selectedIndex1 = j;
				selected1 = true;
			}
			if (weight2 < selectorWeights_->operator[](j))
			{
				selectedIndex2 = j;
				selected2 = true;
			}
			if (selected1 && selected2) break;
		}

		Solution* parent1 = selectors_->operator[](selectedIndex1)->select(referencePopulation_, rng_);
		Solution* parent2 = selectors_->operator[](selectedIndex2)->select(referencePopulation_, rng_);

		// 2. Apply a random crossover operator. Utilize operator weights.
		selectedIndex1 = 0;
		weight1 = rng_->rand() % (crossoverTotal_ + 1);
		for (unsigned int j = 0; j < crossoverOperators_->size(); j++)
		{
			if (weight1 < crossoverWeights_->operator[](j))
			{
				selectedIndex1 = j;
				break;
			}
		}

		std::pair<Solution*, Solution*> offspringPair = crossoverOperators_->operator[](selectedIndex1)->run(parent1, parent2, rng_);
		Solution* offspring1 = offspringPair.first;
		Solution* offspring2 = offspringPair.second;

		// 3. Apply a random mutation operator. Utilize operator weights.
		selectedIndex1 = 0;
		selectedIndex2 = 0;
		weight1 = rng_->rand() % (mutationTotal_ + 1);
		weight2 = rng_->rand() % (mutationTotal_ + 1);
		selected1 = false;
		selected2 = false;
		for (unsigned int j = 0; j < mutationOperators_->size(); j++)
		{
			if (weight1 < mutationWeights_->operator[](j))
			{
				selectedIndex1 = j;
				selected1 = true;
			}
			if (weight2 < mutationWeights_->operator[](j))
			{
				selectedIndex2 = j;
				selected2 = true;
			}
			if (selected1 && selected2) break;
		}

		mutationOperators_->operator[](selectedIndex1)->run(offspring1, rng_);
		mutationOperators_->operator[](selectedIndex1)->run(offspring2, rng_);

		// 4. Apply the final evaluation.
		evaluator_->evaluateFitness(offspring1);
		evaluator_->evaluatePenalty(offspring1);
		evaluator_->evaluateFitness(offspring2);
		evaluator_->evaluatePenalty(offspring2);

		// 5. Push to subPopulation_.
		subPopulation_->addSolution(offspring1);
		subPopulation_->addSolution(offspring2, true);

		std::chrono::steady_clock::time_point clockFinish = std::chrono::steady_clock::now();

		if (std::chrono::duration_cast<std::chrono::nanoseconds>(clockFinish - clockStart).count() / 1000000000.0 > timeMin_)
		{
			delete subPopulation_;
			subPopulation_ = nullptr;
			break;
		}
	}

	referencePopulation_ = nullptr;
}

Population* GARunner::getSubPopulation()
{
	return subPopulation_;
}

void GARunner::run()
{
}

void GARunner::terminate()
{
}

void GARunner::threadFunction()
{
}

