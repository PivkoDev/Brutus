#include <iostream>

#include "Player.h"
#include "Action.h"
#include "..\Tools\Tools.h"

namespace
{
	const float COMM_MIN(0);
	//const float COMM_MIN(5.0);
	const float COMM(0);
	//const float COMM(0.0038);
}

Player::Player() : 
	data_provider("\\Data\\mstall\\"),
	cash(1000.0), //1000 zl na start
	comission(COMM),
	comission_min(COMM_MIN)
{
	std::cout << "Init Player ..." << std::endl;

	//data_provider.parseFile("11BIT.mst");
	//data_provider.parseFile("KGHM.mst");
	//data_provider.parseFile("LCCORP.mst");
	data_provider.parseFile("VIVID.mst");

	data_provider.printSummary();

	rules.push_back(Rule());

	// Zakres od poczatku do konca wszystkie daty.
	range = data_provider.getRange();
}

void
Player::play()
{
	std::cout << "Let's play ... range : " << range << std::endl;

	current_index = 0;

	for (current_index = 0; current_index < range; current_index++)
	{
		rocknroll();

		if (current_index == (range - 1) || current_index == 0)
		{
			printSummary();
		}
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
	StockData* data = data_provider.getData("VIVID");
	if (data == nullptr)
	{
		std::cout << "brak danych" << std::endl;
		return;
	}

	DayData current_day_data = data->getDayData(current_index);

	std::cout << "--- " << current_index << " , " << current_day_data.date;
	std::cout << " : " << cash << " zl " << "---" << std::endl;
	//std::cout << "akcje : " << std::endl;

	float total(0);
	for (auto inv : inventory)
	{
		const std::string stock_name(inv.first);
		const int stock_count(inv.second);
		StockData* data = data_provider.getData(stock_name);
		if (data == nullptr) continue;

		float cost_stock(0.f);
		if (cost.find(stock_name) != cost.end())
		{
			cost_stock = cost[stock_name];
		}

		if (stock_count >= 0)
		{
			DayData day_data = data->getDayData(current_index);
						
			float value = getValue(stock_count, day_data);

			std::cout << " " << stock_name << " : " << stock_count << " : wartosc = " << value << " zl , koszt = "
				      << cost_stock << " zl " << std::endl;

			total += value;
		}
	}

	std::cout << "akcje total : " << total << " zl" << std::endl;
	std::cout << "akcje + kasa : " << (total + cash) << " zl" << std::endl;
	std::cout << "--------- " << std::endl;
}

void
Player::addActionBuy(std::string name, int amount)
{
	actions.push_back(std::make_unique<ActionBuy>(name, amount));
}

void
Player::addActionSell(std::string name, int amount)
{
	actions.push_back(std::make_unique<ActionSell>(name, amount));
}

void 
Player::buy(std::string name, int amount)
{
	StockData* data = data_provider.getData(name);

	if (data == nullptr)
		return;

	if (current_index >= 0 && current_index < data->getDayDataCount())
	{
		DayData day_data = data->getDayData(current_index);
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

			//std::cout << " buy , value:" << total << " (" << value << "+"
			//	<< com << ") amount: " << amount << std::endl;
		}
		
	}
}

void 
Player::sell(std::string name, int amount)
{
	StockData* data = data_provider.getData(name);

	if (data == nullptr)
	{
		return;
	}

	if (current_index >= 0 && current_index < data->getDayDataCount())
	{
		DayData day_data = data->getDayDataReverse(current_index);
		float value = getValue(amount, day_data);
		float com = value * comission;
		if (com < comission_min) com = comission_min;
		float total = value + com;

		//std::cout << " sell , value:" << total << " (" << value << "+"
		//	<< com << ") amount: " << amount << std::endl;
	}
}