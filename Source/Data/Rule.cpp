#include "Rule.h"
#include "Player.h"

void 
Rule::run(Player* player) 
{ 
	if (!player)
	{
		return;
	} 

	int current_index = player->getCurrentIndex();

	for (int i = 0; i < player->data_provider.getDataCount(); i++)
	{
		StockData* stock_data = player->data_provider.getData(i);

		if (stock_data != nullptr)
		{
			player->addActionBuy(stock_data->name, 10);
		}
	}

	for (auto value : player->inventory)
	{
		if (value.second > 9)
		{
			player->addActionSell(value.first, 5);
		}
	}
};