#include "pch.h"
#include "ga.h"
#include <iostream>
#include <stdexcept>
#include <limits>
#include <chrono>
#include <functional>

GA::GA()
{
}

GA::~GA()
{
	if (rng_ != nullptr) delete rng_;
	if (problemData_ != nullptr) delete problemData_;
	if (population_ != nullptr) delete population_;
	if (criteria_ != nullptr) delete criteria_;
	for (PopulationInitializer* populationInitializer : *populationInitializers_)
	{
		delete populationInitializer;
	}
	populationInitializers_->clear();
	delete populationInitializers_;
	for (GARunner* runner : *runners_)
	{
		delete runner;
	}
	runners_->clear();
	delete runners_;
	for (Selector* selector : *selectors_)
	{
		delete selector;
	}
	selectors_->clear();
	delete selectors_;
	for (CrossoverOperator* crossoverOperator : *crossoverOperators_)
	{
		delete crossoverOperator;
	}
	crossoverOperators_->clear();
	delete crossoverOperators_;
	for (MutationOperator* mutationOperator : *mutationOperators_)
	{
		delete mutationOperator;
	}
	mutationOperators_->clear();
	delete mutationOperators_;
	if (evaluator_ != nullptr) delete evaluator_;

	delete bestSolutionTracker_;
}

void GA::setPopulationSize(unsigned int var)
{
	populationSize_ = var;
}

void GA::setThreadCount(unsigned int var)
{
	threadCount_ = var;
}

void GA::setSortOrder(bool reverse)
{
	sortOrder_ = reverse;
}

void GA::setPrintFrequency(unsigned int generationFrequency)
{
	printFrequency_ = generationFrequency;
}

void GA::setRandomNumberGenerator(RNG* rng)
{
	rng_ = rng;
}

void GA::setProblemData(ProblemData* problemData)
{
	problemData_ = problemData;
}

void GA::setTerminationCriteria(TerminationCriteria* criteria)
{
	criteria_ = criteria;
}

void GA::addPopulationInitializer(PopulationInitializer* populationInitializer)
{
	populationInitializers_->push_back(populationInitializer);
}

void GA::addSelector(Selector* selector)
{
	selectors_->push_back(selector);
}

void GA::addCrossoverOperator(CrossoverOperator* crossoverOperator)
{
	crossoverOperators_->push_back(crossoverOperator);
}

void GA::addMutationOperator(MutationOperator* mutationOperator)
{
	mutationOperators_->push_back(mutationOperator);
}

void GA::addPostGenerationOperator(PostGenerationOperator* postGenerationOperator)
{
	postGenerationOperators_->push_back(postGenerationOperator);
}

void GA::setEvaluator(Evaluator* evaluator)
{
	evaluator_ = evaluator;
}

void GA::print()
{
	std::string sortOrder;
	if (sortOrder_) sortOrder = "Highest to Lowest";
	else sortOrder = "Lowest to Highest";
	std::cout << "----- GA Instance Details -----" << std::endl;
	std::cout << "- Thread Count:          " << std::to_string(threadCount_) << std::endl;
	std::cout << "- Population Size:       " << std::to_string(populationSize_) << std::endl;
	std::cout << "- Population Sort Order: " << sortOrder << std::endl;
	std::cout << "- Termination Criteria:  ";
	if (criteria_ == nullptr)
	{
		std::cout << "UNDEFINED" << std::endl;
	}
	else
	{
		std::cout << std::endl;
		std::cout << "  - Minimum Fitness:     " << std::to_string(criteria_->getFitnessMin()) << std::endl;
		std::cout << "  - Maximum Fitness:     " << std::to_string(criteria_->getFitnessMax()) << std::endl;
		std::cout << "  - Minimum Generation:  " << std::to_string(criteria_->getGenerationMin()) << std::endl;
		std::cout << "  - Maximum Generation:  " << std::to_string(criteria_->getGenerationMax()) << std::endl;
		std::cout << "  - Minimum Time (s):    " << std::to_string(criteria_->getTimeMin()) << std::endl;
		std::cout << "  - Maximum Time (s):    " << std::to_string(criteria_->getTimeMax()) << std::endl;
	}
	std::cout << "- Evaluator: ";
	if (evaluator_ == nullptr)
	{
		std::cout << "UNDEFINED" << std::endl;
	}
	else
	{
		evaluator_->print();
	}
	std::cout << "--- Population Initializers ---" << std::endl;
	if (populationInitializers_ == nullptr)
	{
		std::cout << "UNDEFINED" << std::endl;
	}
	else
	{
		for (PopulationInitializer* populationInitializer : *populationInitializers_)
		{
			populationInitializer->print();
		}
	}
	std::cout << "--- Selectors ---" << std::endl;
	if (selectors_ == nullptr)
	{
		std::cout << "UNDEFINED" << std::endl;
	}
	else
	{
		for (Selector* selector : *selectors_)
		{
			selector->print();
		}
	}
	std::cout << "--- Crossover Operators ---" << std::endl;
	if (crossoverOperators_ == nullptr)
	{
		std::cout << "UNDEFINED" << std::endl;
	}
	else
	{
		for (CrossoverOperator* crossoverOperator : *crossoverOperators_)
		{
			crossoverOperator->print();
		}
	}
	std::cout << "--- Mutation Operators ---" << std::endl;
	if (mutationOperators_ == nullptr)
	{
		std::cout << "UNDEFINED" << std::endl;
	}
	else
	{
		for (MutationOperator* mutationOperator : *mutationOperators_)
		{
			mutationOperator->print();
		}
	}
	std::cout << "--- Post-Generation Operators ---" << std::endl;
	if (postGenerationOperators_ == nullptr)
	{
		std::cout << "UNDEFINED" << std::endl;
	}
	else if (postGenerationOperators_->size() == 0)
	{
		std::cout << "UNDEFINED" << std::endl;
	}
	else
	{
		for (PostGenerationOperator* postGenerationOperator : *postGenerationOperators_)
		{
			postGenerationOperator->print();
		}
	}
	if (terminationCode_ != -1)
	{
		std::cout << "--- Execution Results ---" << std::endl;
		std::cout << "- Total Generation Count: " << std::to_string(generation_) << std::endl;
		std::cout << "- Total Time Taken (s):   " << std::to_string(time_) << std::endl;
		//std::cout << "-- Final Population Details --" << std::endl;
		//population_->print();
		std::cout << "-- Discovered Optimal Solution --" << std::endl;
		bestSolutionHistory_->operator[](*bestSolutionTracker_)->print();
	}
}

void GA::run()
{
	// Pre-Initialization. (Checks if everything necessary has been set.)
	if (terminationCode_ != -1)
	{
		// GA instance should only be executed once.
		std::cout << "GA has already been run." << std::endl;
		return;
	}
	if (problemData_ == nullptr ||
		criteria_ == nullptr ||
		populationInitializers_ == nullptr ||
		evaluator_ == nullptr ||
		selectors_ == nullptr ||
		crossoverOperators_ == nullptr ||
		mutationOperators_ == nullptr)
	{
		throw std::exception("One or more necessary variables are not defined (nullptr).");
	}
	if (populationInitializers_->size() == 0)
	{
		throw std::exception("No population initializers have been defined.");
	}
	if (selectors_->size() == 0)
	{
		throw std::exception("No selectors have been defined.");
	}
	if (crossoverOperators_->size() == 0)
	{
		throw std::exception("No crossover operators have been defined.");
	}
	if (mutationOperators_->size() == 0)
	{
		throw std::exception("No mutation operators have been defined.");
	}
	if (postGenerationOperators_ == nullptr)
	{
		postGenerationOperators_ = new std::vector<PostGenerationOperator*>();
	}
	for (PostGenerationOperator* postGenerationOperator : *postGenerationOperators_)
	{
		postGenerationOperator->setupBestSolutionTracking(bestSolutionHistory_, bestSolutionTracker_);
	}

	std::chrono::steady_clock::time_point clockStart = std::chrono::steady_clock::now();

	if (rng_ == nullptr) rng_ = new RNG(0);

	// Population Initialization.
	if (populationInitializers_->size() == 1)
	{
		population_ = populationInitializers_->operator[](0)->createPopulation(populationSize_);
	}
	else
	{
		population_ = new Population(populationSize_);
		std::vector<unsigned int> weights = {};
		unsigned int cumulativeWeight = 0;
		for (PopulationInitializer* initializer : *populationInitializers_)
		{
			unsigned int initializerWeight = initializer->getUseWeight();
			cumulativeWeight += initializerWeight;
			weights.push_back(cumulativeWeight);
		}

		for (unsigned int i = 0; i < populationSize_; i++)
		{
			unsigned int initializerSelector = 0;
			unsigned int weight = rand() % (cumulativeWeight + 1);
			for (unsigned int j = 0; j < populationInitializers_->size(); j++)
			{
				if (weight < weights[j])
				{
					initializerSelector = j;
					break;
				}
			}

			Solution* solution = populationInitializers_->operator[](initializerSelector)->createSolution();
			population_->addSolution(solution);
		}
	}
	population_->setSortOrder(sortOrder_);
	population_->sort();
	population_->assessment();
	bestSolutionHistory_->push_back(population_->getSolution(0));

	if (printFrequency_ > 0)
	{
		std::chrono::steady_clock::time_point clockInitialization = std::chrono::steady_clock::now();
		std::string initializationTime = std::to_string(std::chrono::duration_cast<std::chrono::nanoseconds>(clockInitialization - clockStart).count() / 1000000000.0);
		std::cout << "Population has been initialized (Time taken: " + initializationTime + " s)" << std::endl;
	}

	createGARunners();
	std::function<bool(Solution*, Solution*)> solutionComparator;
	if (sortOrder_)
	{
		// Reversed (the higher fitness, the better)
		solutionComparator = [](Solution* lhs, Solution* rhs) {return *lhs > *rhs; };
	}
	else
	{
		// Normal (the lower fitness, the better)
		solutionComparator = [](Solution* lhs, Solution* rhs) {return *lhs < *rhs; };
	}

	// Main Loop.
	const unsigned int GENERATION_MAX = criteria_->getGenerationMax();
	const unsigned int GENERATION_MIN = criteria_->getGenerationMin();
	const long double TIME_MAX = criteria_->getTimeMax();
	const long double TIME_MIN = criteria_->getTimeMin();

	std::function<void()> loopPrinter;
	if (printFrequency_ > 0)
	{
		// Print GA status for each generation.
		loopPrinter = [&]() {
			if (generation_ % printFrequency_ != 0) return;
			std::string maxGen = "Generation: " + std::to_string(generation_) + " / " + std::to_string(GENERATION_MAX) + " | ";
			std::string minGen = "Minimum Generation: " + std::to_string(generationMin_) + " / " + std::to_string(GENERATION_MIN) + " | ";
			float generationBestFitness = bestSolutionHistory_->operator[](generation_)->getFitness();
			float overallBestFitness = bestSolutionHistory_->operator[](*bestSolutionTracker_)->getFitness();
			std::string fitnessGen = "Best Generation Fitness / Best Overall Fitness: " + std::to_string(generationBestFitness) + " / " + std::to_string(overallBestFitness);
			std::cout << maxGen << minGen << fitnessGen << std::endl;
		};
	}
	else
	{
		// Print nothing.
		loopPrinter = []() {};
	}

	loopPrinter();

	while (!criteria_->checkGenerationMin(generationMin_) && !criteria_->checkGenerationMax(generation_) && !criteria_->checkTimeMax(time_))
	{
		Population* newPopulation = createNewPopulation();
		if (newPopulation == nullptr)
		{
			terminationCode_ = 4;
			break;
		}
		newPopulation->setSortOrder(sortOrder_);
		newPopulation->sort();
		newPopulation->assessment();

		++generation_;
		++generationMin_;

		bool postGenerationOperatorsUsed = false;
		for (PostGenerationOperator* postGenerationOperator : *postGenerationOperators_)
		{
			if (generation_ % (postGenerationOperator->getGenerationFrequency()) == 0)
			{
				postGenerationOperatorsUsed = true;
				postGenerationOperator->run(rng_, newPopulation, population_);
			}
		}
		
		population_->replaceSolution(0, nullptr, false);
		delete population_;
		population_ = newPopulation;
		if (postGenerationOperatorsUsed)
		{
			population_->sort();
			population_->assessment();
		}
		
		bestSolutionHistory_->push_back(population_->getSolution(0));
		if (solutionComparator(bestSolutionHistory_->operator[](bestSolutionHistory_->size() - 1), bestSolutionHistory_->operator[](*bestSolutionTracker_)))
		{
			*bestSolutionTracker_ = bestSolutionHistory_->size() - 1;
			generationMin_ = 0;
		}
		
		for (GARunner* runner : *runners_)
		{
			runner->setReferencePopulation(population_);
		}

		std::chrono::steady_clock::time_point clockFinish = std::chrono::steady_clock::now();
		time_ = std::chrono::duration_cast<std::chrono::nanoseconds>(clockFinish - clockStart).count() / 1000000000.0;

		loopPrinter();
	}

	// Conclusion.

	terminateGARunners();
	
	if (criteria_->checkFitness(bestSolutionHistory_->operator[](*bestSolutionTracker_)->getFitness()))
	{
		terminationCode_ = 1;
	}
	else if (criteria_->checkGenerationMin(generationMin_))
	{
		terminationCode_ = 2;
	}
	else if (criteria_->checkGenerationMax(generation_))
	{
		terminationCode_ = 3;
	}
	else if (criteria_->checkTimeMax(time_))
	{
		terminationCode_ = 5;
	}
	else
	{
		terminationCode_ = 0;
	}
}

Solution* GA::getBestSolution()
{
	if (bestSolutionHistory_->size() == 0)
	{
		throw std::exception("No solutions have been recorded yet.");
	}
	else if (bestSolutionHistory_->size() <= *bestSolutionTracker_)
	{
		throw std::out_of_range("Solution tracker is not properly maintained.");
	}
	return bestSolutionHistory_->operator[](*bestSolutionTracker_);
}

unsigned int GA::getTotalGeneration()
{
	return generation_;
}

long double GA::getTotalTime()
{
	return time_;
}

int GA::getTerminationCode()
{
	return terminationCode_;
}

std::vector<Solution*>* GA::getBestSolutionHistory()
{
	return bestSolutionHistory_;
}

void GA::createGARunners()
{
	GARunner* runner = new GARunner(0, populationSize_);
	runner->setReferencePopulation(population_);
	runner->setSelectors(selectors_);
	runner->setCrossoverOperators(crossoverOperators_);
	runner->setMutationOperators(mutationOperators_);
	runner->setEvaluator(evaluator_);
	runner->setRandomNumberGenerator(rng_->clone(1));
	runner->setSolutionTimeout(criteria_->getTimeMin());
	runners_->push_back(runner);
}

Population* GA::createNewPopulation()
{
	runners_->operator[](0)->createSubPopulation();
	if (runners_->operator[](0)->getSubPopulation() != nullptr)
	{
		Population* population = new Population(populationSize_);
		population->mergePopulation(runners_->operator[](0)->getSubPopulation());
		return population;
	}
	else return nullptr;
}

void GA::terminateGARunners()
{
}

