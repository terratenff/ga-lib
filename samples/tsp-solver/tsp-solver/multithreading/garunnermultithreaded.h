#pragma once

#include "garunner.h"
#include <thread>
#include <chrono>
#include <future>

/// <summary>
/// Known issue: std::future_error (future_already_retrieved) is thrown at random. Increasing the frequency
/// at which updates are given (using "setPrintFrequency") might lower the probability of this happening.
/// </summary>
class GARunnerMultithreaded : public GARunner
{
public:
	GARunnerMultithreaded(int id, unsigned int subPopulationSize);
	~GARunnerMultithreaded();
	void run() override;
	void terminate() override;

	std::shared_future<bool> getFuture();
	void setTaskFuture(std::shared_future<bool> taskFuture);
	void setTaskConclusionFuture(std::shared_future<bool> taskConclusionFuture);
	void join();
private:
	void threadFunction() override;
	bool started_ = false;
	bool terminationRequested_ = false;
	std::thread thread_;

	/// <summary>
	/// Used to let the GA instance know that a subpopulation has been completed.
	/// </summary>
	std::promise<bool> promise_;

	/// <summary>
	/// Using this runners wait for the GA instance to give the signal for
	/// creating subpopulations.
	/// </summary>
	std::shared_future<bool> taskFuture_;

	/// <summary>
	/// Using this runners wait for the GA instance to reset its base promise.
	/// </summary>
	std::shared_future<bool> taskConclusionFuture_;

	/// <summary>
	/// Used as a makeshift solution to an issue where runners are left hanging at random.
	/// </summary>
	std::shared_future<bool> taskConclusionFutureOld_;
};
