#include <NavalCommand/Classification/Api/SubCategory.h>
#include <NavalCommand/Units/Api/Type.h>
#include <gtest/gtest.h>
#include <type_traits>
#include <vector>

namespace Classification = NavalCommand::Classification::Api;
namespace Equipment = NavalCommand::Equipment::Api;
namespace Units = NavalCommand::Units::Api;

static_assert(std::is_same_v<decltype(Units::Type::UnitSubCategory), Classification::SubCategory>);
static_assert(std::is_same_v<decltype(Units::Type::PlatformRoles), std::vector<Classification::Role>>);
static_assert(std::is_same_v<decltype(Equipment::Loadout::Roles), std::vector<Classification::Role>>);

TEST(UnitTypeTest, PrimaryRoleIsExplicitAndIndependentOfCapabilityOrder)
{
	Units::Type type{};
	EXPECT_FALSE(type.PrimaryPlatformRole);
	type.PlatformRoles = {Classification::Role::Surveillance, Classification::Role::AirborneEarlyWarning};
	EXPECT_FALSE(type.PrimaryPlatformRole);
	type.PrimaryPlatformRole = Classification::Role::AirborneEarlyWarning;
	EXPECT_EQ(type.PrimaryPlatformRole, Classification::Role::AirborneEarlyWarning);
	EXPECT_EQ(Units::GetRoles(type), type.PlatformRoles);
}

TEST(UnitTypeTest, DerivesCategoryAndDimensionFromItsSubCategory)
{
	Units::Type type;
	type.Id = {"destroyer"};
	type.UnitSubCategory = Classification::SubCategory::Destroyer;

	EXPECT_EQ(type.Id.Value, "destroyer");
	EXPECT_EQ(Classification::GetCategory(type.UnitSubCategory), Classification::Category::SurfaceVessel);
	EXPECT_EQ(Classification::GetDimension(Classification::GetCategory(type.UnitSubCategory)), Classification::Dimension::SeaSurface);
}

TEST(UnitTypeTest, ReturnsPlatformRolesWhenLoadoutsAreAbsent)
{
	Units::Type type;
	type.PlatformRoles = {
		Classification::Role::AirSuperiority,
		Classification::Role::AirborneEarlyWarning
	};

	const std::vector<Classification::Role> expectedRoles{
		Classification::Role::AirSuperiority,
		Classification::Role::AirborneEarlyWarning
	};

	EXPECT_TRUE(type.Loadouts.empty());
	EXPECT_EQ(Units::GetRoles(type), expectedRoles);
}

TEST(UnitTypeTest, ReturnsLoadoutRolesWhenPlatformRolesAreAbsent)
{
	Units::Type type;
	Equipment::Loadout standard;
	standard.Roles = {
		Classification::Role::AirDefence,
		Classification::Role::SurfaceWarfare
	};
	type.Loadouts.push_back(standard);

	const std::vector<Classification::Role> expectedRoles{
		Classification::Role::AirDefence,
		Classification::Role::SurfaceWarfare
	};

	EXPECT_TRUE(type.PlatformRoles.empty());
	EXPECT_EQ(Units::GetRoles(type), expectedRoles);
}

TEST(UnitTypeTest, DeduplicatesRolesAcrossMultipleLoadouts)
{
	Units::Type type;
	Equipment::Loadout standard;
	standard.Roles = {
		Classification::Role::AirDefence,
		Classification::Role::SurfaceWarfare
	};
	type.Loadouts.push_back(standard);

	Equipment::Loadout alternative;
	alternative.Roles = {
		Classification::Role::SurfaceWarfare,
		Classification::Role::Reconnaissance
	};
	type.Loadouts.push_back(alternative);

	const std::vector<Classification::Role> expectedRoles{
		Classification::Role::AirDefence,
		Classification::Role::SurfaceWarfare,
		Classification::Role::Reconnaissance
	};

	EXPECT_EQ(Units::GetRoles(type), expectedRoles);
}

TEST(UnitTypeTest, CombinesPlatformAndLoadoutRolesInDeterministicUniqueOrder)
{
	Units::Type type;
	type.PlatformRoles = {
		Classification::Role::MaritimePatrol,
		Classification::Role::Reconnaissance,
		Classification::Role::MaritimePatrol
	};

	Equipment::Loadout standard;
	standard.Roles = {
		Classification::Role::AirDefence,
		Classification::Role::Reconnaissance,
		Classification::Role::SurfaceWarfare
	};
	type.Loadouts.push_back(standard);

	Equipment::Loadout alternative;
	alternative.Roles = {
		Classification::Role::AirDefence,
		Classification::Role::Decoy,
		Classification::Role::MaritimePatrol,
		Classification::Role::Decoy
	};
	type.Loadouts.push_back(alternative);

	const std::vector<Classification::Role> expectedRoles{
		Classification::Role::MaritimePatrol,
		Classification::Role::Reconnaissance,
		Classification::Role::AirDefence,
		Classification::Role::SurfaceWarfare,
		Classification::Role::Decoy
	};

	const auto roles = Units::GetRoles(type);
	EXPECT_EQ(roles, expectedRoles);
	EXPECT_EQ(Units::GetRoles(type), expectedRoles);
}

TEST(UnitTypeTest, EmptyPlatformAndLoadoutRolesProduceAnEmptyResult)
{
	Units::Type type;
	EXPECT_TRUE(Units::GetRoles(type).empty());

	type.Loadouts.push_back({});
	type.Loadouts.push_back({});
	EXPECT_TRUE(Units::GetRoles(type).empty());
}
