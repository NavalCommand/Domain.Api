#include <NavalCommand/Simulation/Api/TimeCompressionFactor.h>
#include <gtest/gtest.h>

TEST(TimeCompressionFactorTest, SupportsValueComparison)
{
	const NavalCommand::Simulation::Api::TimeCompressionFactor factor{4.0};
	EXPECT_EQ(factor, NavalCommand::Simulation::Api::TimeCompressionFactor{4.0});
}
