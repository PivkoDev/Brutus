#pragma once

#include <string>

class Player; 


class Action
{
public:
	int quantity;

	virtual void run(Player* player);

};

class ActionBuy : public Action
{
	std::string name;
	int amount;
public:
	ActionBuy();
	ActionBuy(std::string name_set, int amount_set);
	void run(Player* player) override;
};