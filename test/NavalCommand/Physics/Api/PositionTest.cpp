#include <NavalCommand/Physics/Api/Position.h>
#include <gtest/gtest.h>

namespace Physics = NavalCommand::Physics::Api;

TEST(PositionTest, StoresLatitudeLongitudeAndElevation)
{
	const Physics::Position position{{61.96}, {-10.37}, {0}};
	EXPECT_DOUBLE_EQ(position.Latitude.Value, 61.96);
	EXPECT_DOUBLE_EQ(position.Longitude.Value, -10.37);
	EXPECT_DOUBLE_EQ(position.Elevation.Value, 0.0);
}
