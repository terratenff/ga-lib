#include "gamultithreaded.h"
#include "garunnermultithreaded.h"

GAMultithreaded::GAMultithreaded(): GA()
{
	future_ = basePromise_.get_future();
	futureEnd_ = conclusionPromise_.get_future();
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
		static_cast<GARunnerMultithreaded*>(runner)->setTaskFuture(future_);
		runners_->push_back(runner);
	}
}

Population* GAMultithreaded::createNewPopulation()
{
	runnerFutures_.clear();
	for (GARunner* runner : *runners_)
	{
		GARunnerMultithreaded* runnerMT = static_cast<GARunnerMultithreaded*>(runner);
		std::shared_future<bool> runnerFuture = runnerMT->getFuture();
		runnerFutures_.push_back(runnerFuture);
		runnerMT->setTaskConclusionFuture(futureEnd_);
		runner->run();
	}
	basePromise_.set_value(true);
	basePromise_ = std::promise<bool>();
	future_ = basePromise_.get_future();

	for (unsigned int i = 0; i < runners_->size(); i++)
	{
		runnerFutures_[i].wait();
		static_cast<GARunnerMultithreaded*>(runners_->operator[](i))->setTaskFuture(future_);
	}

	Population* population = new Population(populationSize_);
	for (GARunner* runner : *runners_)
	{
		Population* subPopulation = runner->getSubPopulation();
		if (subPopulation != nullptr) population->mergePopulation(subPopulation);
		else return nullptr;
	}

	conclusionPromise_.set_value(true);
	conclusionPromise_ = std::promise<bool>();
	futureEnd_ = conclusionPromise_.get_future();

	return population;
}

void GAMultithreaded::terminateGARunners()
{
	for (GARunner* runner : *runners_)
	{
		runner->terminate();
	}
	basePromise_.set_value(true);
	for (GARunner* runner : *runners_)
	{
		static_cast<GARunnerMultithreaded*>(runner)->join();
	}
}
