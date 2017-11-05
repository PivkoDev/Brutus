#include "Init_GLUT.h"

IListener* Init_GLUT::listener = nullptr;
WindowInfo Init_GLUT::window_information;

void Init_GLUT::init(const WindowInfo& window,
					 const ContextInfo& context,
					 const FramebufferInfo& framebuffer)
{
	//we need to create these fake arguments
	int fakeargc = 1;
	char *fakeargv[] = { "fake", NULL };
	glutInit(&fakeargc, fakeargv);

	//if (context.core)
	//{
	//	glutInitContextVersion(context.major_version,
	//						   context.minor_version);
	//	glutInitContextProfile(GLUT_CORE_PROFILE);
	//}
	//else
	//{
	//	// version doesn't matter in Compatibility mode
	//	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	//}
	
	glutInitDisplayMode(framebuffer.flags);
	glutInitWindowPosition(window.position_x, window.position_y);
	glutInitWindowSize(window.width, window.height);

	glutCreateWindow(window.name.c_str());

	std::cout << "GLUT:initialized" << std::endl;

	//these callbacks are used for rendering
	glutIdleFunc(idleCallback);
	glutCloseFunc(closeCallback);
	glutDisplayFunc(displayCallback);
	glutReshapeFunc(reshapeCallback);

	//cleanup
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE,
		          GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	//our method to display some info. Needs contextInfo and windowinfo
	printOpenGLInfo(window, context);

	window_information = window;
}

//starts the rendering Loop
void Init_GLUT::run()
{
	std::cout << "GLUT:\t Start Running " << std::endl;
	glutMainLoop();
}

void Init_GLUT::close()
{
	std::cout << "GLUT:\t Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init_GLUT::idleCallback(void)
{
	//do nothing, just redisplay
	glutPostRedisplay();
}

void Init_GLUT::displayCallback()
{
	//check for NULL
	if (listener)
	{
		listener->notifyBeginFrame();
		listener->notifyDisplayFrame();

		glutSwapBuffers();

		listener->notifyEndFrame();
	}
}

void Init_GLUT::reshapeCallback(int width, int height)
{
	if (window_information.is_reshapable == true)
	{
		if (listener)
		{
			listener->notifyReshape(
				width,	height,
				window_information.width,
				window_information.height);
		}
		window_information.width = width;
		window_information.height = height;
	}
}

void Init_GLUT::closeCallback()
{
	close();
}

void Init_GLUT::enterFullscreen()
{
	glutFullScreen();
}

void Init_GLUT::exitFullscreen()
{
	glutLeaveFullScreen();
}

void Init_GLUT::printOpenGLInfo(const WindowInfo& window,
								const ContextInfo& context)
{
	const unsigned char* renderer = glGetString(GL_RENDERER);
	const unsigned char* vendor = glGetString(GL_VENDOR);
	const unsigned char* version = glGetString(GL_VERSION);

	std::cout << "******************************************************               ************************" << std::endl;
	std::cout << "GLUT:Initialise" << std::endl;
	std::cout << "GLUT:\tVendor : " << vendor << std::endl;
	std::cout << "GLUT:\tRenderer : " << renderer << std::endl;
	std::cout << "GLUT:\tOpenGl version: " << version << std::endl;
}

void Init_GLUT::setListener(IListener*& iListener)
{
	listener = iListener;
}