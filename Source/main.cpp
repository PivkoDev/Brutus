#include <iostream>

#include "framework.h"

#include "NeuroNets\Net.h"
#include "Tools\Serializer.h"
#include "Data\Player.h"

int main(int argc, char **argv)
{
	std::cout << "Brutus v.0.1 started.\n";
	Tools::timeMeasureStart();

	//remind_init();
	
	Net neural_net;
	//Serializer serializer;
	//serializer.deserialize(neural_net);

	Player player(neural_net);
	Tools::timeMeasureStamp();

	player.play();
	Tools::timeMeasureStamp();

	//remind_render();
	//serializer.serialize(neural_net);

	system("pause");
	
	return 0;
}