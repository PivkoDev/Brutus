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
	std::vector<DayData> data;

public:
	std::string name;
	
	StockData() : name("") {};

	DayData getDayDataReverse(int index);
	int getDayDataCount();
	void addData(DayData day_data);
};

