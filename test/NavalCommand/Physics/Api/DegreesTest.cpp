#include <NavalCommand/Physics/Api/Degrees.h>
#include <NavalCommand/Physics/Api/Radians.h>
#include <gtest/gtest.h>
#include <type_traits>

namespace Physics = NavalCommand::Physics::Api;

static_assert(!std::is_convertible_v<Physics::Degrees, Physics::Radians>);

TEST(DegreesTest, StoresItsValueWithoutImplicitAngleConversion)
{
	const Physics::Degrees latitude{61.96};
	EXPECT_DOUBLE_EQ(latitude.Value, 61.96);
}
