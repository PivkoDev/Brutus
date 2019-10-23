#include <iostream>

#include "NeuroNets\Net.h"
#include "Tools\Serializer.h"
#include "Data\Player.h"


#include "framework.h"




int main(int argc, char **argv)
{
	std::cout << "Brutus v.0.1 started.\n";
	Tools::timeMeasureStart();

	remind_init();

	// Logika : sieci neuronowe.
	//Net NeuralNet;
	//Serializer serializer;
	//serializer.deserialize(NeuralNet);

	Player player;
	Tools::timeMeasureStamp();

	player.play();
	Tools::timeMeasureStamp();

	// Rysowanie : OpenGL
	remind_render();
	
	// Sprzatanie

	//serializer.serialize(NeuralNet);


	return 0;
}