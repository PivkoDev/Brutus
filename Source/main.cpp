#include "glew.h"
#include "freeglut.h"
#include <iostream>

#include "..\Managers\ShaderManager.h"
#include "..\Core\GameModels.h"

#include "..\Source\NeuroNets\Net.h"
#include "..\Source\Serializer.h"

/*
 
*/

GameModels* gameModels;
GLuint program;
ShaderManager* shader_manager;

void RenderScene(void)
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glBindVertexArray(gameModels->GetModel("triangle1"));
	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void CloseCallback()
{
	std::cout << "GLUT: Finished" << std::endl;
	glutLeaveMainLoop();
}

void Init()
{
	glEnable(GL_DEPTH_TEST);

	gameModels = new GameModels();
	gameModels->CreateTriangleModel("triangle1");

	shader_manager = new ShaderManager();
	shader_manager->CreateProgram(
		"ColorShader1",
		"D:\\C\\Projekty\\Brutus\\Shaders\\VertexShader.glsl",
		"D:\\C\\Projekty\\Brutus\\Shaders\\FragmentShader.glsl");
	program = ShaderManager::GetShader("ColorShader1");

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

int main(int argc, char **argv)
{
	std::cout << "Brutus v.0.1 started.\n";

	// Root object
	Net NeuralNet;
	Serializer serializer;
	//serializer.deserialize(NeuralNet);
	//NeuralNet.init();
	NeuralNet.setUpTestNetwork();
	//NeuralNet.setUpTestNetworkSimple();
	NeuralNet.print();
	//NeuralNet.learn(1, 1);
	//NeuralNet.print();
	//NeuralNet.learn(1, 1000);
	//NeuralNet.print();
	//NeuralNet.learn(1, 10000);
	//NeuralNet.print();
	//NeuralNet.learn(1, 100000);
	//NeuralNet.print();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(500, 500);//optional
	glutInitWindowSize(800, 600); //optional

	glutCreateWindow("Brutus v.0.1");
	glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glewInit();
	std::cout << "Using glew " << glewGetString(GLEW_VERSION) << "\n";

	if (glewIsSupported("GL_VERSION_4_3"))
	{
		std::cout << " GLEW Version is 4.3\n ";
	}
	else
	{
		std::cout << "GLEW 4.3 not supported\n ";
	}

	Init();

	// register callbacks
	glutDisplayFunc(RenderScene);
	glutCloseFunc(CloseCallback);

	glutMainLoop();

	serializer.serialize(NeuralNet);

	delete gameModels;
	delete shader_manager;

	glDeleteProgram(program);
	
	return 0;
}