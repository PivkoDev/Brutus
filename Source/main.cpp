#include "glew.h"
#include "freeglut.h"
#include <iostream>

#include "Managers\ShaderManager.h"
#include "Managers\SceneManager.h"

#include "NeuroNets\Net.h"
#include "Serializer.h"
#include "Data\Player.h"

#include "Core\Init_GLUT.h"
#include "Core\Init_GLEW.h"


int main(int argc, char **argv)
{
	std::cout << "Brutus v.0.1 started.\n";

	// Logika : sieci neuronowe.
	//Net NeuralNet;
	//Serializer serializer;
	//serializer.deserialize(NeuralNet);
	//NeuralNet.init();
	//NeuralNet.setUpTestNetwork();
	//NeuralNet.setUpTestNetworkSimple();
	//NeuralNet.print();
	//NeuralNet.learn(1, 1);
	//NeuralNet.print();
	Player player;
	player.play(10);
		
	// Rysowanie : OpenGL
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
	
	// Sprzatanie

	//serializer.serialize(NeuralNet);


	return 0;
}