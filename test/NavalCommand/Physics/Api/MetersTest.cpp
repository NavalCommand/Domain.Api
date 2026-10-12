#include <NavalCommand/Physics/Api/Meters.h>
#include <NavalCommand/Physics/Api/Seconds.h>
#include <gtest/gtest.h>
#include <type_traits>

namespace Physics = NavalCommand::Physics::Api;

static_assert(!std::is_convertible_v<Physics::Meters, Physics::Seconds>);

TEST(MetersTest, StoresItsValue)
{
	const Physics::Meters elevation{125.0};
	EXPECT_DOUBLE_EQ(elevation.Value, 125.0);
}
