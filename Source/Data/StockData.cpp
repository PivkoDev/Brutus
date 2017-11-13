#include "StockData.h"

DayData
StockData::getDayDataReverse(int index)
{
	int index_from_end = data.size() - 1 - index;
	if (index_from_end<data.size() && index_from_end>=0)
	{
		return data[index_from_end];
	}
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