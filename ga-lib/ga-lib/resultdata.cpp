#include "pch.h"
#include "resultdata.h"
#include <iostream>
#include <string>
#include <fstream>

ResultData::ResultData(Solution* solution, long double time, int generation, int terminationCode):
	solution_(solution),
	time_(time),
	generation_(generation),
	terminationCode_(terminationCode)
{
}

void ResultData::print()
{
	if (!isDataConstructed_)
	{
		isDataConstructed_ = true;
		constructData();
	}
	std::cout << "--------------------------- GA Execution Results ---------------------------" << std::endl;
	std::cout << std::endl;
	printAlgorithmData();
	printSolutionData();
	std::cout << "----------------------------------------------------------------------------" << std::endl;
}

void ResultData::save(std::string path)
{
	std::string text = "--------------------------- GA Execution Results ---------------------------\n";
	std::string algorithmText = makeAlgorithmString();
	std::string solutionText = makeSolutionString();
	text += algorithmText + solutionText;
	text += "----------------------------------------------------------------------------\n";

	std::ofstream file;
	file.open(path + ".txt");
	file << text;
	file.close();
}

void ResultData::printAlgorithmData()
{
	std::cout << makeAlgorithmString() << std::endl;
}

void ResultData::printSolutionData()
{
	std::cout << makeSolutionString() << std::endl;
}

std::string ResultData::makeAlgorithmString()
{
	if (!isDataConstructed_)
	{
		isDataConstructed_ = true;
		constructData();
	}
	std::string text = "";
	text += "- Algorithm Execution Details ----------------------------------------------\n";
	switch (terminationCode_)
	{
	case 0:
		// 0: No premature termination / Undefined.
		text += "Algorithm execution has been prematurely terminated due to an unexpected error.\n";
		break;
	case 1:
		// 1: A fitness criterion was broken.
		text += "Algorithm execution has been prematurely terminated due to a fitness criterion being broken.\n";
		break;
	case 2:
		// 2: Minimum generation criterion was broken.
		text += "Algorithm execution has been prematurely terminated due to minimum generation criterion being broken.\n";
		break;
	case 3:
		// 3: Maximum generation criterion was broken.
		text += "Algorithm execution has been prematurely terminated due to maximum generation criterion criterion being broken.\n";
		break;
	case 4:
		// 4: Minimum time criterion was broken.
		text += "Algorithm execution has been prematurely terminated due to minimum time criterion being broken.\n";
		break;
	case 5:
		// 5: Maximum time criterion was broken.
		text += "Algorithm execution has been prematurely terminated due to maximum time criterion being broken.\n";
		break;
	case -1:
		// 0: No premature termination / Undefined.
		text += "Algorithm execution has been prematurely terminated due to an unexpected error.\n";
		break;
	default:
		// None of the above: Something unexpected happened.
		text += "Algorithm execution has been prematurely terminated due to an unexpected error. (Termination Code: " + std::to_string(terminationCode_) + ")\n";
		break;
	}
	text += "Number of Generations Iterated: " + std::to_string(generation_) + "\n";
	text += "Total Time Taken (seconds):     " + std::to_string(time_) + "\n";
	text += "----------------------------------------------------------------------------\n";

	return text;
}
