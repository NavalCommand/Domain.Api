#include <NavalCommand/Units/Api/Id.h>
#include <NavalCommand/Observations/Api/Id.h>
#include <gtest/gtest.h>
#include <type_traits>

static_assert(!std::is_same_v<NavalCommand::Units::Api::Id, NavalCommand::Observations::Api::Id>);

TEST(UnitIdTest, StoresAuthoritativeIdentity)
{
	const NavalCommand::Units::Api::Id id{"unit-carrier"};
	EXPECT_EQ(id.Value, "unit-carrier");
}
