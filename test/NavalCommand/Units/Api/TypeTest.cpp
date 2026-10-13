#include <NavalCommand/Classification/Api/Taxonomy.h>
#include <NavalCommand/Units/Api/Type.h>
#include <gtest/gtest.h>
#include <vector>

namespace Classification = NavalCommand::Classification::Api;
namespace Units = NavalCommand::Units::Api;

TEST(UnitTypeTest, StoresDesignedRolesAndSubCategory)
{
	Units::Type type;
	type.Id = {"destroyer"};
	type.UnitCategory = Classification::Category::SurfaceVessel;
	type.UnitSubCategory = Classification::SubCategory::Destroyer;
	type.DesignedRoles = std::vector<Classification::Role>{
		Classification::Role::AirDefence,
		Classification::Role::AntiSubmarineWarfare
	};
	type.Loadouts.push_back({});

	EXPECT_EQ(type.Id.Value, "destroyer");
	ASSERT_TRUE(type.UnitSubCategory.has_value());
	EXPECT_TRUE(Classification::IsConsistent(*type.UnitCategory, *type.UnitSubCategory));
	EXPECT_EQ(Classification::GetDimension(*type.UnitCategory), Classification::Dimension::SeaSurface);
	ASSERT_TRUE(type.DesignedRoles.has_value());
	ASSERT_EQ(type.DesignedRoles->size(), 2);
	EXPECT_EQ(type.DesignedRoles->front(), Classification::Role::AirDefence);
	EXPECT_EQ(type.Loadouts.size(), 1);
}

TEST(UnitTypeTest, UnknownRoleInformationIsNotAnEmptyRoleList)
{
	Units::Type type;
	EXPECT_FALSE(type.UnitCategory.has_value());
	EXPECT_FALSE(type.UnitSubCategory.has_value());
	EXPECT_FALSE(type.DesignedRoles.has_value());

	type.DesignedRoles.emplace();
	EXPECT_TRUE(type.DesignedRoles->empty());
}
