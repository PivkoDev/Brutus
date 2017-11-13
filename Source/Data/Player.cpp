#include "Player.h"
#include "Action.h"

#include <iostream>

Player::Player() : 
	data_provider("\\Data\\mstall\\"),
	cash(1000.0), //1000 zl na start
	comission(0.0038),
	comission_min(5.0)
{
	std::cout << "Init Player ..." << std::endl;

	data_provider.parseFile("11BIT.mst");
	data_provider.parseFile("KGHM.mst");
	data_provider.parseFile("LCCORP.mst");
	data_provider.printSummary();

	rules.push_back(Rule());
	
}

void
Player::play(int range)
{
	std::cout << "Let's play ..." << std::endl;
	current_index = range;

	for (int i = 0; i < range; i++)
	{
		rocknroll();

		if(i==(range-1))
			printSummary();

		current_index--;
	}
}

void
Player::rocknroll()
{
	for (auto rule : rules)
	{
		rule.run(this);
	}

	for (auto& action : actions)
	{
		action->run(this);
	}

	actions.clear();
}

float
Player::getValue(int amount, DayData& day_data)
{
	float buying_price = day_data.open
		+ ((day_data.close - day_data.open) / 2);
	
	float ret = amount * buying_price;
	//std::cout << "getValue(" << amount << "):" << ret << std::endl;
	return ret;
}

void
Player::printSummary()
{
	std::cout << "--- " << current_index << "---" << std::endl;
	std::cout << "kasa : " << cash << " zl " <<  std::endl;
	std::cout << "akcje : " << std::endl;
	for (auto inv : inventory)
	{
		StockData data = data_provider.getData(inv.first);

		float cost_stock(0.f);
		if (cost.find(inv.first) != cost.end())
		{
			cost_stock = cost[inv.first];
		}

		if (inv.second >= 0 && inv.second < data.getDayDataCount())
		{
			DayData day_data = data.getDayDataReverse(current_index);
			float value = getValue(inv.second, day_data);
			std::cout << " - " << inv.first << " : " << inv.second
				<< " : " << value << " zl , "
				<< cost_stock << " zl " << day_data.date << std::endl;
		}
	}

	std::cout << "--------- " << std::endl;
}

void
Player::addActionBuy(std::string name, int amount)
{
	actions.push_back(std::make_unique<ActionBuy>(name, amount));
}

void 
Player::buy(std::string name, int amount)
{
	StockData data = data_provider.getData(name);
	
	if (current_index >= 0 && current_index < data.getDayDataCount())
	{
		DayData day_data = data.getDayDataReverse(current_index);
		float value = getValue(amount, day_data);
		float com = value * comission;
		if (com < comission_min) com = comission_min;
		float total = value + com;

		

		if (total <= cash)
		{
			if (inventory.find(name) != inventory.end())
			{
				inventory[name] += amount;
			}
			else
			{
				inventory[name] = amount;
			}
			if (cost.find(name) != cost.end())
			{
				cost[name] += total;
			}
			else
			{
				cost[name] = total;
			}

			cash -= total;

			std::cout << " buy , value:" << total << " (" << value << "+"
				<< com << ") amount: " << amount << std::endl;
		}
		
	}
}

void 
Player::sell(std::string name, int amount)
{

}