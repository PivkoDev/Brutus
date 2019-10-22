#pragma once

#include <string>
#include <map>
#include "StockData.h"

class DataProvider
{
private:
	std::string data_path;
	std::vector<StockData> data_all_stocks;
	std::vector<std::string> parts_last_parse;

public:
	DataProvider(std::string path);
	void parseDir(std::string path);
	void parseFile(std::string path);
	void parseLine(std::string line);


	void addData(StockData& stock_data);
	StockData* getData(int index);
	StockData* getData(std::string name);
	int getDataCount();

	void printSummary();

	int getRange();
	
};