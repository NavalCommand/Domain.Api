#include <NavalCommand/Environment/Api/Error.h>
#include <gtest/gtest.h>

TEST(EnvironmentErrorTest, ExposesInvalidCoordinateFailure)
{
	EXPECT_NE(NavalCommand::Environment::Api::Error::InvalidCoordinates,
		NavalCommand::Environment::Api::Error::InvalidTerrain);
}
