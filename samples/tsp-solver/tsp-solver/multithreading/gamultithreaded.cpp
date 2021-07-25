#include "gamultithreaded.h"
#include "garunnermultithreaded.h"
#include <iostream>

GAMultithreaded::GAMultithreaded(): GA()
{
	timeoutErrors_.reserve(threadCount_);
}

GAMultithreaded::~GAMultithreaded()
{
	delete conditionVariable_;
	delete mutex_;
	for (bool* ready : readyStates_) delete ready;
}

void GAMultithreaded::createGARunners()
{
	unsigned int subPopulationSize = populationSize_ / threadCount_;
	unsigned int leftover = populationSize_ % threadCount_;
	for (unsigned int i = 1; i <= threadCount_; i++)
	{
		unsigned int designatedSize = subPopulationSize;
		if (i == threadCount_) designatedSize += leftover;
		GARunner* runner = new GARunnerMultithreaded(int(i), designatedSize);
		runner->setReferencePopulation(population_);
		runner->setSelectors(selectors_);
		runner->setCrossoverOperators(crossoverOperators_);
		runner->setMutationOperators(mutationOperators_);
		runner->setEvaluator(evaluator_);
		runner->setRandomNumberGenerator(rng_->clone(i));
		runner->setSolutionTimeout(criteria_->getTimeMin());
		static_cast<GARunnerMultithreaded*>(runner)->setConditionVariable(conditionVariable_);
		static_cast<GARunnerMultithreaded*>(runner)->setMutex(mutex_);
		runners_->push_back(runner);
		readyStates_.push_back(new bool(false));
		static_cast<GARunnerMultithreaded*>(runner)->setReadyState(readyStates_[i - 1]);
		timeoutErrors_.push_back(false);
	}
}

Population* GAMultithreaded::createNewPopulation()
{
	futures_.clear();
	for (GARunner* runner : *runners_)
	{
		GARunnerMultithreaded* runnerMT = static_cast<GARunnerMultithreaded*>(runner);
		std::promise<bool>* promise = new std::promise<bool>();
		runnerMT->setPromise(promise);
		futures_.push_back(runnerMT->getFuture());
		runner->run();
	}

	for (bool* ready : readyStates_) *ready = true;
	conditionVariable_->notify_all();

	// Makeshift patch, part 1 / 2.
	timeoutErrorTracker_ = 0;
	for (unsigned int i = 0; i < runners_->size(); i++)
	{
		std::future_status status = futures_[i]->wait_for(std::chrono::milliseconds(TIMEOUT_ERROR_THRESHOLD_));
		if (status == std::future_status::timeout)
		{
			// Runner has taken too long, and thus, has been declared "left hanging".
			// The subpopulation that it is in charge of is marked for replacement.
			timeoutErrors_[i] = true;
			std::cout << "Timeout error occurred. Attempting subpopulation replacement..." << std::endl;
		}
	}

	Population* population = new Population(populationSize_);
	for (GARunner* runner : *runners_)
	{
		Population* subPopulation = runner->getSubPopulation();

		// Makeshift patch, part 2 / 2.
		if (timeoutErrors_[timeoutErrorTracker_])
		{
			unsigned int subPopulationSize = subPopulation->size();
			//delete subPopulation;
			// Attempting to deallocate the damaged subpopulation results in complications.
			// For the time being, the deallocation procedure is skipped, resulting in a conscious memory leak.
			// Replacement subpopulation is created using the first defined population initializer.
			subPopulation = populationInitializers_->operator[](0)->createPopulation(subPopulationSize);
			timeoutErrors_[timeoutErrorTracker_] = false;
		}
		if (subPopulation != nullptr) population->mergePopulation(subPopulation);
		else return nullptr;
		++timeoutErrorTracker_;
	}

	return population;
}

void GAMultithreaded::terminateGARunners()
{
	for (GARunner* runner : *runners_)
	{
		runner->terminate();
	}
	
	for (bool* ready : readyStates_) *ready = true;
	conditionVariable_->notify_all();

	for (GARunner* runner : *runners_)
	{
		static_cast<GARunnerMultithreaded*>(runner)->join();
	}
}
