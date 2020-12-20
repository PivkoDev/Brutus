#include <iostream>

#include "StockData.h"

DayData
StockData::getDayDataReverse(size_t index)
{
	auto index_from_end = data.size() - 1 - index;
	if (index_from_end < data.size() && index_from_end >= 0)
	{
		return data[index_from_end];
	}

	return DayData();
}

DayData
StockData::getDayData(size_t index)
{
	if (index >= 0 && index < data.size() )
	{
		return data[index];
	}

	return DayData();
}

void
StockData::addData(DayData day_data)
{
	data.push_back(day_data);
}

int 
StockData::getDayDataCount()
{
	return data.size();
}

void
StockData::sort()
{
	data_sorted.clear();

	for (auto& day_data : data)
	{
		int date_as_int = stoi(day_data.date);

		data_sorted[date_as_int] = day_data;
	}

	auto last_element = data_sorted.end();
	last_element--;

	std::cout << "sort stock : " << name << " : size : " << data_sorted.size() << " ";
	std::cout << "min : " << data_sorted.begin()->first << " max : " << last_element->first << std::endl;
}