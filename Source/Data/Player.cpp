#include "Player.h"

#include <iostream>

Player::Player() : 
	data_provider("\\Data\\mstall\\"),
	cash(1000.0) //1000 zl na start
{
	std::cout << "Init Player ..." << std::endl;

	data_provider.parseFile("11BIT.mst");
	data_provider.printSummary();
}

void
Player::play(int range)
{
	std::cout << "Let's play ..." << std::endl;

	for (int i = 0; i < range; i++)
	{
		rocknroll();
		printSummary(i);
	}
}

void
Player::rocknroll()
{
	for (auto rule : rules)
	{

	}

	for (auto action : actions)
	{
		
	}
}

void
Player::printSummary(int index)
{
	std::cout << "--- " << index << "---" << std::endl;
	std::cout << "kasa : " << cash << " zl " <<  std::endl;

	std::cout << "--------- " << std::endl;
}