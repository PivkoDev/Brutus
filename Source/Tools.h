#pragma once

#include <string>
#include <vector>

#define EL std::endl;

class Tools
{
public:
	static void 
	splitString(const std::string& input, std::vector<std::string>& out,
							const std::string delim);

	void 
	writeData(std::ofstream& , std::string, std::string);
};