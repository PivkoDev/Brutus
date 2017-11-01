#pragma once

#include <string>

class WindowInfo
{
public:
	std::string name;
	int width, height;
	int position_x, position_y;
	bool is_reshapable;

	WindowInfo()
	{
		name = "Brutus v.0.1";
		width = 800;
		height = 600;
		position_x = 300;
		position_y = 300;
		is_reshapable = true;
	}

	WindowInfo(
		std::string& name,
		int pos_x, int pos_y,
		int w, int h,
		bool is_reshapable)
	{
		this->name = name;
		this->position_x = pos_x;
		this->position_y = pos_y;
		this->width = w;
		this->height = h;
		this->is_reshapable = is_reshapable;

	}

	WindowInfo(const WindowInfo& copy)
	{
		name = copy.name;
		position_x = copy.position_x;
		position_y = copy.position_y;
		width = copy.width;
		height = copy.height;
		is_reshapable = copy.is_reshapable;
	}

	void operator=(const WindowInfo& assign)
	{
		name = assign.name;
		position_x = assign.position_x;
		position_y = assign.position_y;
		width = assign.width;
		height = assign.height;
		is_reshapable = assign.is_reshapable;
	}
};

