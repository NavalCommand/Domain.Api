#include <NavalCommand/Units/Api/Type.h>
#include <gtest/gtest.h>

TEST(UnitTypeTest, StoresClassificationAndLoadoutsWithItsIdentity)
{
	NavalCommand::Units::Api::Type type;
	type.Id = {"carrier"};
	type.Loadouts.push_back({});
	EXPECT_EQ(type.Id.Value, "carrier");
	EXPECT_EQ(type.Loadouts.size(), 1);
}
