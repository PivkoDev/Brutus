#pragma once

#include "WindowInfo.h"
#include "FrameBufferInfo.h"
#include "ContextInfo.h"
#include "IListener.h"
#include "Init_GLEW.h"
#include <iostream>

class Init_GLUT
{
private:
	static IListener* listener;
	static WindowInfo window_information;

public:             
	static void init(const WindowInfo& window,
			         const ContextInfo& context,
					 const FramebufferInfo& framebuffer);

	static void setListener(IListener*& iListener);

public:
	static void run();//called from outside
	static void close();

	void enterFullscreen();
	void exitFullscreen();

	//used to print info about GL
	static void printOpenGLInfo(const WindowInfo& window,
							    const ContextInfo& context);
private:
	static void idleCallback(void);
	static void displayCallback(void);
	static void reshapeCallback(int width, int height);
	static void closeCallback();
};
