#include "Player.h"

#include <iostream>

Player::Player() : data_provider("\\Data\\mstall\\")
{
	std::cout << "Init Player ..." << std::endl;

	data_provider.parseFile("11BIT.mst");
}