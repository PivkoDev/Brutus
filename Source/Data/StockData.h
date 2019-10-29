#pragma once

#include <map>
#include <string>
#include <vector>

/**
 *	One day data of stock price.
 */
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

/**
 *	Single share prices.
 */
class StockData
{
	/**
	 *	Array with daily rates.
	 */
	std::vector<DayData> data;

	/**
	 *	Constructor.
	 */
	std::map<int, DayData> data_sorted;

public:
	/**
	 *	Stock name.
	 */
	std::string name;
	
	StockData() : name("") {};

	DayData getDayDataReverse(int index);
	DayData getDayData(int index);
	int getDayDataCount();
	void addData(DayData day_data);
	
	/**
	 *	Update map with sorted data by date.
	 */
	void sort();
};

