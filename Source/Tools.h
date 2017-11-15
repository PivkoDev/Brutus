#pragma once

#include <string>
#include <vector>
#include <chrono>

#define EL std::endl;

class Tools
{
	static
	std::chrono::high_resolution_clock::time_point time_stamp;

public:
	static void 
	splitString(const std::string& input, std::vector<std::string>& out,
							const std::string delim);

	void 
	writeData(std::ofstream& , std::string, std::string);

	static void
	timeMeasureStart();

	static void
	timeMeasureStamp(std::string msg="");

	
};