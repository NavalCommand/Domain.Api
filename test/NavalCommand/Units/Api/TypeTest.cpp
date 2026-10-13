#include <NavalCommand/Classification/Api/SubCategory.h>
#include <NavalCommand/Units/Api/Type.h>
#include <gtest/gtest.h>
#include <type_traits>
#include <vector>

namespace Classification = NavalCommand::Classification::Api;
namespace Equipment = NavalCommand::Equipment::Api;
namespace Units = NavalCommand::Units::Api;

static_assert(std::is_same_v<decltype(Units::Type::UnitSubCategory), Classification::SubCategory>);

TEST(UnitTypeTest, DerivesCategoryDimensionAndRolesFromLoadouts)
{
	Units::Type type;
	type.Id = {"destroyer"};
	type.UnitSubCategory = Classification::SubCategory::Destroyer;

	Equipment::Loadout standard;
	standard.Id = {"standard"};
	standard.Roles = {
		Classification::Role::AirDefence,
		Classification::Role::AntiSubmarineWarfare
	};
	type.Loadouts.push_back(standard);

	Equipment::Loadout alternative;
	alternative.Id = {"alternative"};
	alternative.Roles = {
		Classification::Role::AirDefence,
		Classification::Role::SurfaceWarfare
	};
	type.Loadouts.push_back(alternative);

	EXPECT_EQ(type.Id.Value, "destroyer");
	EXPECT_EQ(Classification::GetCategory(type.UnitSubCategory), Classification::Category::SurfaceVessel);
	EXPECT_EQ(Classification::GetDimension(Classification::GetCategory(type.UnitSubCategory)), Classification::Dimension::SeaSurface);
	ASSERT_EQ(type.Loadouts.size(), 2);

	const auto roles = Units::GetRoles(type);
	ASSERT_EQ(roles.size(), 3);
	EXPECT_EQ(roles[0], Classification::Role::AirDefence);
	EXPECT_EQ(roles[1], Classification::Role::AntiSubmarineWarfare);
	EXPECT_EQ(roles[2], Classification::Role::SurfaceWarfare);
}

TEST(UnitTypeTest, EmptyLoadoutsAndUnspecifiedRolesProduceEmptyResults)
{
	Units::Type type;
	type.UnitSubCategory = Classification::SubCategory::FixedWingAircraft;
	EXPECT_TRUE(Units::GetRoles(type).empty());

	type.Loadouts.push_back({});
	EXPECT_TRUE(Units::GetRoles(type).empty());

	type.Loadouts.front().Roles.push_back(Classification::Role::Reconnaissance);
	auto roles = Units::GetRoles(type);
	ASSERT_EQ(roles.size(), 1);
	EXPECT_EQ(roles.front(), Classification::Role::Reconnaissance);

	type.Loadouts.push_back({});
	roles = Units::GetRoles(type);
	ASSERT_EQ(roles.size(), 1);
	EXPECT_EQ(roles.front(), Classification::Role::Reconnaissance);
}
