#include "garunnermultithreaded.h"
#include <iostream>

GARunnerMultithreaded::GARunnerMultithreaded(int id, unsigned int subPopulationSize):
	GARunner(id, subPopulationSize)
{
}

GARunnerMultithreaded::~GARunnerMultithreaded()
{
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

std::shared_future<bool> GARunnerMultithreaded::getFuture()
{
	return promise_.get_future();
}

void GARunnerMultithreaded::setTaskFuture(std::shared_future<bool> taskFuture)
{
	taskFuture_ = taskFuture;
}

void GARunnerMultithreaded::setTaskConclusionFuture(std::shared_future<bool> taskConclusionFuture)
{
	taskConclusionFutureOld_ = taskConclusionFuture_;
	taskConclusionFuture_ = taskConclusionFuture;
}

void GARunnerMultithreaded::join()
{
	thread_.join();
}

void GARunnerMultithreaded::threadFunction()
{
	while (!terminationRequested_)
	{
		std::future_status status = taskFuture_.wait_for(std::chrono::milliseconds(10000));
		if (terminationRequested_)
		{
			//std::cout << "Terminating runner..." << std::endl;
			break;
		}
		else if (status == std::future_status::timeout)
		{
			std::cout << "A runner has been terminated due to not receiving a task." << std::endl;
			break;
		}
		else if (status == std::future_status::ready)
		{
			createSubPopulation();
			promise_.set_value(true);
			promise_ = std::promise<bool>();
			std::future_status status2 = taskConclusionFuture_.wait_for(std::chrono::milliseconds(2000));
			if (status2 == std::future_status::timeout)
			{
				std::cout << "A runner has been terminated since it has been left hanging." << std::endl;
				break;
			}
		}
		else
		{
			std::cout << "A runner has been terminated due to an unknown reason." << std::endl;
			break;
		}
	}
}
