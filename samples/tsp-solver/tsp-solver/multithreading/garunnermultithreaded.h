#pragma once

#include "garunner.h"
#include <thread>
#include <chrono>
#include <future>
#include <mutex>
#include <condition_variable>

/// <summary>
/// Known issue: Future element provided by a runner is left hanging at random.
/// A makeshift patch is applied to circumvent damages that it causes for the time being.
/// </summary>
class GARunnerMultithreaded : public GARunner
{
public:
	GARunnerMultithreaded(int id, unsigned int subPopulationSize);
	~GARunnerMultithreaded();
	void run() override;
	void terminate() override;
	void join();

	void setConditionVariable(std::condition_variable* conditionVariable);
	void setMutex(std::mutex* mutex);
	void setPromise(std::promise<bool>* promise);
	std::future<bool>* getFuture();
	void setReadyState(bool* ready);
private:
	void threadFunction() override;
	bool started_ = false;
	bool terminationRequested_ = false;
	std::thread thread_;

	/// <summary>
	/// Used to organize runners: parameters of the runners have to be configured
	/// every generation prior to subpopulation creation. This makes sure that they
	/// do not proceed prematurely.
	/// </summary>
	std::condition_variable* conditionVariable_ = nullptr;

	/// <summary>
	/// Used to control synchronization with the condition variable.
	/// </summary>
	std::mutex* mutex_ = nullptr;

	/// <summary>
	/// Used to let the GA instance know that a subpopulation has been completed.
	/// Runners use it to send the signal.
	/// </summary>
	std::promise<bool>* promise_ = nullptr;

	/// <summary>
	/// Used to let the GA instance know that a subpopulation has been completed.
	/// Runners pass it over for the GA instance.
	/// </summary>
	std::future<bool>* future_ = nullptr;

	/// <summary>
	/// Used to catch those runners that do not reach the condition variable before
	/// the main thread.
	/// </summary>
	bool* ready_ = nullptr;
};
