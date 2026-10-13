#include <NavalCommand/Classification/Api/Taxonomy.h>
#include <NavalCommand/Units/Api/Type.h>
#include <gtest/gtest.h>
#include <vector>

namespace Classification = NavalCommand::Classification::Api;
namespace Equipment = NavalCommand::Equipment::Api;
namespace Units = NavalCommand::Units::Api;

TEST(UnitTypeTest, DerivesDesignedRolesFromLoadouts)
{
	Units::Type type;
	type.Id = {"destroyer"};
	type.UnitCategory = Classification::Category::SurfaceVessel;
	type.UnitSubCategory = Classification::SubCategory::Destroyer;

	Equipment::Loadout standard;
	standard.Id = {"standard"};
	standard.Roles = std::vector<Classification::Role>{
		Classification::Role::AirDefence,
		Classification::Role::AntiSubmarineWarfare
	};
	type.Loadouts.push_back(standard);

	Equipment::Loadout alternative;
	alternative.Id = {"alternative"};
	alternative.Roles = std::vector<Classification::Role>{
		Classification::Role::AirDefence,
		Classification::Role::SurfaceWarfare
	};
	type.Loadouts.push_back(alternative);

	EXPECT_EQ(type.Id.Value, "destroyer");
	ASSERT_TRUE(type.UnitSubCategory.has_value());
	EXPECT_TRUE(Classification::IsConsistent(*type.UnitCategory, *type.UnitSubCategory));
	EXPECT_EQ(Classification::GetDimension(*type.UnitCategory), Classification::Dimension::SeaSurface);
	ASSERT_EQ(type.Loadouts.size(), 2);

	const auto roles = Units::GetRoles(type);
	ASSERT_TRUE(roles.has_value());
	ASSERT_EQ(roles->size(), 3);
	EXPECT_EQ((*roles)[0], Classification::Role::AirDefence);
	EXPECT_EQ((*roles)[1], Classification::Role::AntiSubmarineWarfare);
	EXPECT_EQ((*roles)[2], Classification::Role::SurfaceWarfare);
}

TEST(UnitTypeTest, DoesNotTreatMissingRoleDataAsEmpty)
{
	Units::Type type;
	EXPECT_FALSE(type.UnitCategory.has_value());
	EXPECT_FALSE(type.UnitSubCategory.has_value());
	EXPECT_FALSE(Units::GetRoles(type).has_value());

	type.Loadouts.push_back({});
	EXPECT_FALSE(Units::GetRoles(type).has_value());

	type.Loadouts.front().Roles.emplace();
	const auto roles = Units::GetRoles(type);
	ASSERT_TRUE(roles.has_value());
	EXPECT_TRUE(roles->empty());

	type.Loadouts.push_back({});
	EXPECT_FALSE(Units::GetRoles(type).has_value());
}
