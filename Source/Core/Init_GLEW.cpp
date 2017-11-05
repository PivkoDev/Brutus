#include "Init_GLEW.h"
#include <iostream>

void Init_GLEW::Init()
{
	if (glewInit() == GLEW_OK)
	{
		std::cout << "Using glew " << glewGetString(GLEW_VERSION) << "\n";
	}

	if (glewIsSupported("GL_VERSION_4_3"))
	{
		std::cout << " GLEW Version is 4.3\n ";
	}
	else
	{
		std::cout << "GLEW 4.3 not supported\n ";
	}
}