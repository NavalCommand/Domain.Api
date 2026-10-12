#include <NavalCommand/Simulation/Api/Error.h>
#include <gtest/gtest.h>

TEST(SimulationErrorTest, IncludesBlocked)
{
	EXPECT_NE(NavalCommand::Simulation::Api::Error::Blocked,
		NavalCommand::Simulation::Api::Error::InvalidTimeCompression);
}
