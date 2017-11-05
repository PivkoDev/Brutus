#pragma once

#include <string>
#include <vector>

class DayData
{
public:
	std::string date;
	float open;
	float high;
	float low;
	float close;
	int volume;
};

class StockData
{
public:
	std::string name;
	std::vector<DayData> data;

	StockData() : name("") {};
};

