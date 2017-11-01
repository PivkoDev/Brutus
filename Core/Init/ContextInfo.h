#pragma once

#include <string>

class ContextInfo 
{
public:
	
	int major_version;
	int minor_version;
	bool core;

	ContextInfo()
	{
		major_version = 4;
		minor_version = 3;
		core = true;
	}

	ContextInfo(int major_version, int minor_version,
		        bool core)
	{
		this->major_version = major_version;
		this->minor_version = minor_version;
		this->core = core;
	}
};