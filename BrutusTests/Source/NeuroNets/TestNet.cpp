#include <gtest/gtest.h>

#include "..\..\..\Source\NeuroNets\Net.h"

TEST(NetTest, testCtor)
{
	Net net;

	ASSERT_EQ(net.getInputCount(), 0);
	ASSERT_EQ(net.getOutputCount(), 0);

}