#include "Action.h"
#include "Player.h"

void
Action::run(Player* player)
{
}

ActionBuy::ActionBuy()
{
	amount = 0;
	name = "";
}

ActionBuy::ActionBuy(std::string name_set, int amount_set)
{
	name = name_set;
	amount = amount_set;
}

void 
ActionBuy::run(Player* player)
{
	if (player)
	{
		player->buy(name, amount);
	}
}

ActionSell::ActionSell()
{
	amount = 0;
	name = "";
}

ActionSell::ActionSell(std::string name_set, int amount_set)
{
	name = name_set;
	amount = amount_set;
}

void
ActionSell::run(Player* player)
{
	if (player)
	{
		player->sell(name, amount);
	}
}