#pragma once

#include "DataProvider.h"
#include "Rule.h"
#include "Action.h"
#include <vector>

class Player
{
private:
	DataProvider data_provider;
	float cash;
	std::vector<Rule> rules;
	std::vector<Action> actions;

public:
	Player();

public:
	// logika
	void play(int range=0);
	void rocknroll();


	// informacje
	void printSummary(int index);

};