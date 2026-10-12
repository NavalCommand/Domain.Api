#include <NavalCommand/Equipment/Api/Loadout.h>
#include <gtest/gtest.h>

namespace Equipment = NavalCommand::Equipment::Api;

TEST(LoadoutTest, OwnsItsFits)
{
	Equipment::Loadout loadout;
	loadout.Id = {"patrol"};
	Equipment::Fit fit;
	fit.TypeId = {"external-tank"};
	loadout.Equipment.push_back(fit);

	ASSERT_EQ(loadout.Equipment.size(), 1);
	EXPECT_EQ(loadout.Id.Value, "patrol");
	EXPECT_EQ(loadout.Equipment.front().TypeId.Value, "external-tank");
}
