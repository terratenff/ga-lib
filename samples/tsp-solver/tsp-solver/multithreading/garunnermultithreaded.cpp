#include "garunnermultithreaded.h"
#include <iostream>

GARunnerMultithreaded::GARunnerMultithreaded(int id, unsigned int subPopulationSize):
	GARunner(id, subPopulationSize)
{
}

GARunnerMultithreaded::~GARunnerMultithreaded()
{
	if (promise_ != nullptr) delete promise_;
	if (future_ != nullptr) delete future_;
}

void GARunnerMultithreaded::run()
{
	if (!started_)
	{
		started_ = true;
		thread_ = std::thread(&GARunnerMultithreaded::threadFunction, this);
	}
}

void GARunnerMultithreaded::terminate()
{
	terminationRequested_ = true;
}

void GARunnerMultithreaded::join()
{
	thread_.join();
}

void GARunnerMultithreaded::setConditionVariable(std::condition_variable* conditionVariable)
{
	conditionVariable_ = conditionVariable;
}

void GARunnerMultithreaded::setMutex(std::mutex* mutex)
{
	mutex_ = mutex;
}

void GARunnerMultithreaded::setPromise(std::promise<bool>* promise)
{
	if (promise_ != nullptr) delete promise_;
	promise_ = promise;
	if (future_ != nullptr) delete future_;
	future_ = new std::future<bool>(promise_->get_future());
}

std::future<bool>* GARunnerMultithreaded::getFuture()
{
	return future_;
}

void GARunnerMultithreaded::setReadyState(bool* ready)
{
	ready_ = ready;
}

void GARunnerMultithreaded::threadFunction()
{
	while (!terminationRequested_)
	{
		{
			std::unique_lock<std::mutex> lock(*mutex_);
			while (!*ready_) conditionVariable_->wait(lock);
			*ready_ = false;
			lock.unlock();
		}
		if (terminationRequested_)
		{
			break;
		}
		else
		{
			createSubPopulation();
			promise_->set_value(true);
		}
	}
}
