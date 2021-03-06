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
DataProvider::parseDir(std::string path)
{

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

	stock_data.sort();

	data_all_stocks.push_back(stock_data);
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

		stock_data.addData(day_data);
	}
}

StockData* 
DataProvider::getData(size_t index)
{
	if (index >= 0 && index < data_all_stocks.size())
	{
		return &data_all_stocks[index];
	}
	else
	{
		return nullptr;
	}
}

StockData*
DataProvider::getData(std::string name)
{
	for(StockData& stock_data : data_all_stocks)
	{
		if (stock_data.name == name)
		{
			return &stock_data;
		}
	}

	return nullptr;
}

int
DataProvider::getDataCount()
{
	return data_all_stocks.size();
}

void
DataProvider::printSummary()
{
	std::cout << "_DataProvider size :" << data_all_stocks.size() << std::endl;

	for(auto stock_data : data_all_stocks)
	{
		DayData first_day_data = stock_data.getDayData(0);
		
		const int last_day_index = stock_data.getDayDataCount() - 1;
		DayData last_day_data = stock_data.getDayData(last_day_index);
		
		std::cout << " name :" << stock_data.name 
			<< " days :" << stock_data.getDayDataCount()
			<< " first day : " << first_day_data.date
			<< " last day : " << last_day_data.date << std::endl;
	}
}

int
DataProvider::getRange()
{
	int max_range(0);
	
	// TODO : narazie zakres to pierwsze akcje calosc
	if (data_all_stocks.size() > 0)
	{
		max_range = data_all_stocks.back().getDayDataCount();
	}

	return max_range;
}