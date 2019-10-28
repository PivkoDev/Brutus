#pragma once

#include "../NeuroNets/Decision.h"
#include "../NeuroNets/Net.h"

class Player;

class Rule
{
	Decision decision;

public:
	Rule(Net& neural_net);
	void run(Player* player);
};