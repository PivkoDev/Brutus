#pragma once

#include "DataProvider.h"
#include "Rule.h"
#include "Action.h"
#include "../NeuroNets/Net.h"
#include <vector>
#include <memory>

class Action;

class Player
{
private:
	
	float cash;
	int current_index;
	int range;
	std::vector<Rule> rules;
	std::vector<std::unique_ptr<Action>> actions;
	std::map<std::string, float> cost;
	const float comission;
	const float comission_min;

public:
	Player(Net& neural_net);

public:
	DataProvider data_provider;

	// logika
	void play();
	void rocknroll();
	int getCurrentIndex() { return current_index; };

	// ceny
	float getValue(int amount, DayData& day_data);
	float getCash() { return cash; };

	// aktualny stan
	std::map<std::string, int> inventory;
	
	// informacje
	void printSummary();

	// akcje
	void addActionBuy(std::string name, int amount);
	void addActionSell(std::string name, int amount);
	void buy(std::string name, int amount);
	void sell(std::string name, int amount);


};