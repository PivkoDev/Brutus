#include "Tools.h"

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


