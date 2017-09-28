#include <gtest/gtest.h>

int main(int ac, char* av[])
{
	testing::InitGoogleTest(&ac, av);
	RUN_ALL_TESTS();
	system("pause");
	return 0;
}

