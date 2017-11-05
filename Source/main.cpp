#include "glew.h"
#include "freeglut.h"
#include <iostream>

#include "Managers\ShaderManager.h"
#include "Managers\SceneManager.h"

#include "NeuroNets\Net.h"
#include "Serializer.h"

#include "Core\Init_GLUT.h"
#include "Core\Init_GLEW.h"

GLuint program;
ShaderManager* shader_manager;

void RenderScene(void)
{
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(program);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glutSwapBuffers();
}

void Init()
{
	glEnable(GL_DEPTH_TEST);

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
		

	WindowInfo window(std::string("Brutus v.0.1"),
				      400, 200, 800, 600, true);
	ContextInfo context(4, 5, true);
	FramebufferInfo frameBufferInfo(true, true, true, true);
	Init_GLUT::init(window, context, frameBufferInfo);
	Init_GLEW::Init();

	IListener* scene = new SceneManager();
	Init_GLUT::setListener(scene);
	Init_GLUT::run();

	delete scene;
	
	//serializer.serialize(NeuralNet);


	return 0;
}