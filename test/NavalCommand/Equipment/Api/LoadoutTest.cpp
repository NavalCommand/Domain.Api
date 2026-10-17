#include <NavalCommand/Classification/Api/Role.h>
#include <NavalCommand/Equipment/Api/Loadout.h>
#include <gtest/gtest.h>
#include <vector>

namespace Classification = NavalCommand::Classification::Api;
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

TEST(LoadoutTest, CarriesConfigurationRoles)
{
	Equipment::Loadout loadout;
	EXPECT_TRUE(loadout.Roles.empty());

	loadout.Roles = std::vector<Classification::Role>{
		Classification::Role::AirDefence,
		Classification::Role::AirSuperiority
	};
	ASSERT_EQ(loadout.Roles.size(), 2);
	EXPECT_EQ(loadout.Roles.front(), Classification::Role::AirDefence);

	loadout.Roles.clear();
	EXPECT_TRUE(loadout.Roles.empty());
}
