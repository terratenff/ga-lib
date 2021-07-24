#pragma once

#include "ga.h"
#include <vector>
#include <future>

/// <summary>
/// Known issue: std::future_error (future_already_retrieved) is thrown at random. Increasing the frequency
/// at which updates are given (using "setPrintFrequency") might lower the probability of this happening.
/// </summary>
class GAMultithreaded : public GA
{
public:
	GAMultithreaded();
private:
	void createGARunners() override;
	Population* createNewPopulation() override;
	void terminateGARunners() override;

	/// <summary>
	/// Used to give the signal for the runners to start creating subpopulations.
	/// </summary>
	std::promise<bool> basePromise_;

	/// <summary>
	/// Used to give the GA instance the opportunity to reset the base promise.
	/// </summary>
	std::promise<bool> conclusionPromise_;

	/// <summary>
	/// This is given to the runners so that they can wait for the signal that
	/// the GA instance gives for creating the subpopulations.
	/// </summary>
	std::shared_future<bool> future_;

	/// <summary>
	/// This is given to the runners so that they can wait for the GA instance
	/// to reset the base promise.
	/// </summary>
	std::shared_future<bool> futureEnd_;

	/// <summary>
	/// Used to wait for the runners to finish creating subpopulations.
	/// </summary>
	std::vector<std::shared_future<bool>> runnerFutures_;
};