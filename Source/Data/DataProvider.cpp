#include "DataProvider.h"

#include <iostream>
#include <fstream>
#include <boost/filesystem.hpp>

DataProvider::DataProvider(std::string path)
{
	data_path = boost::filesystem::current_path().string() + path;
	std::cout << "Init DataProvider ... " << data_path << std::endl;
}

void 
DataProvider::parseFile(std::string path)
{
	std::string total_path = data_path + path;
	std::ifstream input_stream(total_path);
	
	if (!input_stream.good())
	{
		std::cout << "Nie moge otworzyc pliku: " << total_path << std::endl;
	}





}