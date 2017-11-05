#pragma once

#include <string>

class DataProvider
{
private:
	std::string data_path;;

public:
	DataProvider(std::string path);

	void parseFile(std::string path);
};