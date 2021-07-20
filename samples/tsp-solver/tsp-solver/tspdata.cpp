#include "tspdata.h"
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <cmath>

TSPData::TSPData(): ProblemData()
{
}

TSPData::TSPData(std::string path, bool matrix): ProblemData()
{
    if (matrix) loadMatrix(path);
    else loadCoordinates(path, true);
}

void TSPData::print()
{
    std::cout << "Problem Data" << std::endl;
    std::cout << "Coordinates" << std::endl << "------------------------" << std::endl;
    for (std::pair<int, int>& pair : coordinates_)
    {
        std::cout << std::to_string(pair.first) + " " + std::to_string(pair.second) << std::endl;
    }

    std::cout << "Matrix" << std::endl << "------------------------" << std::endl;
    for (std::vector<float>& line : matrix_)
    {
        for (float distance : line)
        {
            std::cout << std::to_string(distance) + " ";
        }
        std::cout << std::endl;
    }
}

void TSPData::loadMatrix(std::string path)
{
    matrix_ = {};
    std::fstream file;
    file.open(path, std::ios::in);
    if (file.is_open())
    {
        std::string line;
        std::string delimiter = " ";
        while (std::getline(file, line))
        {
            std::vector<float> matrixLine = {};
            size_t pos = 0;
            std::string token;
            while (pos != std::string::npos)
            {
                pos = line.find(delimiter);
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                matrixLine.push_back(std::stof(token));
            }
            matrix_.push_back(matrixLine);
        }
        file.close();
        problemSize_ = matrix_.size();
    }
    else
    {
        throw std::exception("File reading error occurred.");
    }
}

void TSPData::loadCoordinates(std::string path, bool generateMatrix)
{
    coordinates_ = {};
    std::fstream file;
    file.open(path, std::ios::in);
    if (file.is_open())
    {
        std::string line;
        std::string delimiter = " ";
        while (std::getline(file, line))
        {
            std::vector<int> coordinateList = {};
            size_t pos = 0;
            std::string token;
            while (pos != std::string::npos)
            {
                pos = line.find(delimiter);
                token = line.substr(0, pos);
                line.erase(0, pos + delimiter.length());
                coordinateList.push_back(std::stoi(token));
            }
            std::pair<int, int> coordinatePair;
            coordinatePair.first = coordinateList[0];
            coordinatePair.second = coordinateList[1];
            coordinates_.push_back(coordinatePair);
        }
        file.close();
        problemSize_ = coordinates_.size();
    }
    else
    {
        throw std::exception("File reading error occurred.");
    }

    if (generateMatrix)
    {
        matrix_ = {};
        for (unsigned int i = 0; i < coordinates_.size(); i++)
        {
            std::vector<float> matrixLine = {};
            std::pair<int, int>& pair1 = coordinates_[i];

            for (unsigned int j = 0; j < coordinates_.size(); j++)
            {
                std::pair<int, int>& pair2 = coordinates_[j];
                int x1 = pair1.first;
                int x2 = pair2.first;
                int y1 = pair1.second;
                int y2 = pair2.second;
                float distance = float(sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2)));
                matrixLine.push_back(distance);
            }

            matrix_.push_back(matrixLine);
        }
    }
}

const std::vector<std::vector<float>>& TSPData::getMatrix() const
{
    return matrix_;
}

const std::vector<std::pair<int, int>>& TSPData::getCoordinates() const
{
    return coordinates_;
}

const unsigned int TSPData::getProblemSize() const
{
    return problemSize_;
}
