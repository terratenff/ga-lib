#pragma once

#include "problemdata.h"
#include <vector>
#include <string>

/// <summary>
/// Contains data relevant to the normal TSP: coordinates and related path table.
/// </summary>
class TSPData: public ProblemData
{
public:

	/// <summary>
	/// Initializes the data instance without any data.
	/// </summary>
	TSPData();

	/// <summary>
	/// Initializes the data instance with path table and/or coordinates.
	/// </summary>
	/// <param name="path">Path to file. File suffix must be included.</param>
	/// <param name="matrix">
	/// true = Target file contains a matrix. Only the path table is created.
	/// false = Target file contains coordinates. Both coordinates and a path table are created.
	/// </param>
	TSPData(std::string path, bool matrix = true);
	void print() override;
	void loadMatrix(std::string path);
	void loadCoordinates(std::string path, bool generateMatrix);
	const std::vector<std::vector<float>>& getMatrix() const;
	const std::vector<std::pair<int, int>>& getCoordinates() const;
	const unsigned int getProblemSize() const;
private:
	std::vector<std::vector<float>> matrix_;
	std::vector<std::pair<int, int>> coordinates_;
	unsigned int problemSize_ = 0;
};

