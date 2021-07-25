#pragma once

#include "ga.h"
#include <vector>
#include <future>
#include <mutex>
#include <condition_variable>

/// <summary>
/// Known issue: Future element provided by a runner is left hanging at random.
/// A makeshift patch is applied to circumvent damages that it causes for the time being.
/// </summary>
class GAMultithreaded : public GA
{
public:
	GAMultithreaded();
	~GAMultithreaded();
private:
	void createGARunners() override;
	Population* createNewPopulation() override;
	void terminateGARunners() override;

	/// <summary>
	/// Used to organize runners: parameters of the runners have to be configured
	/// every generation prior to subpopulation creation. This makes sure that they
	/// do not proceed prematurely.
	/// </summary>
	std::condition_variable* conditionVariable_ = new std::condition_variable();

	/// <summary>
	/// Used to control synchronization with the condition variable.
	/// </summary>
	std::mutex* mutex_ = new std::mutex();

	/// <summary>
	/// Used to wait for the runners to finish creating subpopulations.
	/// </summary>
	std::vector<std::future<bool>*> futures_;

	/// <summary>
	/// Collection of flags that the GA instance uses in sending signals to those runners
	/// that have arrived at the condition variable later than the main thread.
	/// </summary>
	std::vector<bool*> readyStates_;

	/// <summary>
	/// One of three variables used in the makeshift patch. Determines
	/// how long the GA instance is allowed to wait before declaring the runner
	/// it's waiting on as "left hanging". It should be modified to such an extent
	/// that it only catches the specified issue (instead of catching successful scenarios
	/// that just happened to take too long).
	/// </summary>
	const unsigned int TIMEOUT_ERROR_THRESHOLD_ = 1000;

	/// <summary>
	/// One of three variables used in the makeshift patch. Keeps track of those runners
	/// that have been left hanging. It is then used to replace subpopulations that have
	/// been damaged by the hanging runners.
	/// </summary>
	std::vector<bool> timeoutErrors_;

	/// <summary>
	/// One of three variables used in the makeshift patch. Simply acts as a tracker
	/// while the GA instance waits for runners to finish.
	/// </summary>
	unsigned int timeoutErrorTracker_ = 0;
};
