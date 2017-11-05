#include "DataProvider.h"

#include <iostream>
#include <fstream>
#include <sstream>
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

	StockData stock_data;
	std::string line;
	int line_index = 0;
	while (std::getline(input_stream, line))
	{
		parseLine(line);

		if (line_index == 1 && parts_last_parse.size()>0)
		{
			stock_data.name = parts_last_parse[0];
		}

		if (line_index > 0)
		{
			addData(stock_data);
		}

		line_index++;
	}

	data.push_back(stock_data);
}

void
DataProvider::parseLine(std::string line)
{	
	parts_last_parse.clear();

	std::istringstream in_line(line);
	std::string part;
	while (std::getline(in_line, part, ','))
	{
		parts_last_parse.push_back(part);
	}
}

void 
DataProvider::addData(StockData& stock_data)
{
	if (parts_last_parse.size() > 6)
	{
		DayData day_data;

		day_data.date = parts_last_parse[1];
		day_data.open = std::stof(parts_last_parse[2]);
		day_data.high = std::stof(parts_last_parse[3]);
		day_data.low = std::stof(parts_last_parse[4]);
		day_data.close = std::stof(parts_last_parse[5]);
		day_data.volume = std::stoi(parts_last_parse[6]);

		stock_data.data.push_back(day_data);
	}
}

void
DataProvider::printSummary()
{
	std::cout << "_DataProvider size :" << data.size() << std::endl;
	if (data.size() > 0)
	{
		std::cout << " [0] name :" << data[0].name << std::endl;
		std::cout << " [0] days :" << data[0].data.size() << std::endl;
	}


}