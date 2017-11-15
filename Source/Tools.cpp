#include "Tools.h"
#include <iostream>

void Tools::splitString(const std::string& input, std::vector<std::string>& out, 
						const std::string delim)
{
	auto i = 0;
	auto pos = input.find(delim);

	while (pos != std::string::npos)
	{
		out.push_back(input.substr(i, pos - i));
		i = ++pos;
		pos = input.find(delim, pos);

		if (pos == std::string::npos)
		{
			out.push_back(input.substr(i, input.length()));
		}
	}

}

std::chrono::high_resolution_clock::time_point Tools::time_stamp = std::chrono::high_resolution_clock::now();

void
Tools::timeMeasureStart()
{
	
	time_stamp = std::chrono::high_resolution_clock::now();

	std::cout << "# time measure start #" << std::endl;
}

void
Tools::timeMeasureStamp(std::string msg)
{
	auto time_stamp_2 = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> time_span = 
		std::chrono::duration_cast<std::chrono::duration<double>>(time_stamp_2 - time_stamp);

	std::cout << "# time took : " << time_span.count() << " sec. " << msg  << std::endl;
	timeMeasureStart();
}


