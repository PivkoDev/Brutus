#pragma once

#include "../NeuroNets/Decision.h"
#include "../NeuroNets/Net.h"

class Player;

class Rule
{
	Decision decision;
	Net& neural_net;

public:
	Rule(Net& net);
	void run(Player* player);
};