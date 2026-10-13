#include <NavalCommand/Classification/Api/Taxonomy.h>
#include <gtest/gtest.h>
#include <cstdint>

namespace Classification = NavalCommand::Classification::Api;

static_assert(Classification::GetDimension(Classification::Category::Aircraft) == Classification::Dimension::Air);
static_assert(Classification::GetDimension(Classification::Category::Submarine) == Classification::Dimension::SeaSubsurface);
static_assert(Classification::GetDimension(Classification::Category::LandEquipment) == Classification::Dimension::Land);
static_assert(Classification::GetCategory(Classification::SubCategory::Destroyer) == Classification::Category::SurfaceVessel);
static_assert(Classification::GetCategory(Classification::SubCategory::CruiseMissile) == Classification::Category::Missile);
static_assert(!Classification::IsConsistent(Classification::Category::Aircraft, Classification::SubCategory::Destroyer));

TEST(TaxonomyTest, EveryCurrentCategoryHasADimension)
{
	const Classification::Category categories[]{
		Classification::Category::Aircraft,
		Classification::Category::Missile,
		Classification::Category::SurfaceVessel,
		Classification::Category::Submarine,
		Classification::Category::Torpedo,
		Classification::Category::Mine,
		Classification::Category::LandEquipment,
		Classification::Category::LandInstallation,
		Classification::Category::LandUnit,
		Classification::Category::SpaceObject
	};

	for (const auto category : categories)
	{
		EXPECT_TRUE(Classification::GetDimension(category).has_value());
	}
}

TEST(TaxonomyTest, AllDeclaredSubCategoriesHaveAParent)
{
	const Classification::SubCategory subCategories[]{
		Classification::SubCategory::FixedWingAircraft,
		Classification::SubCategory::RotaryWingAircraft,
		Classification::SubCategory::TiltRotorAircraft,
		Classification::SubCategory::CruiseMissile,
		Classification::SubCategory::BallisticMissile,
		Classification::SubCategory::AircraftCarrier,
		Classification::SubCategory::Cruiser,
		Classification::SubCategory::Destroyer,
		Classification::SubCategory::Frigate,
		Classification::SubCategory::Corvette,
		Classification::SubCategory::PatrolVessel,
		Classification::SubCategory::AmphibiousVessel,
		Classification::SubCategory::AuxiliaryVessel,
		Classification::SubCategory::MerchantVessel,
		Classification::SubCategory::AttackSubmarine,
		Classification::SubCategory::BallisticMissileSubmarine,
		Classification::SubCategory::CruiseMissileSubmarine,
		Classification::SubCategory::HeavyweightTorpedo,
		Classification::SubCategory::LightweightTorpedo,
		Classification::SubCategory::NavalMine,
		Classification::SubCategory::GroundVehicle,
		Classification::SubCategory::SurfaceToAirMissileLauncher,
		Classification::SubCategory::AntiAircraftGun,
		Classification::SubCategory::Radar,
		Classification::SubCategory::Airfield,
		Classification::SubCategory::MilitaryInstallation,
		Classification::SubCategory::CivilianInstallation
	};

	for (const auto subCategory : subCategories)
	{
		EXPECT_TRUE(Classification::GetCategory(subCategory).has_value());
	}
}

TEST(TaxonomyTest, RejectsInvalidEnumValuesWithoutFabricatingCategories)
{
	const auto invalidCategory = static_cast<Classification::Category>(255);
	const auto invalidSubCategory = static_cast<Classification::SubCategory>(255);
	EXPECT_FALSE(Classification::GetDimension(invalidCategory).has_value());
	EXPECT_FALSE(Classification::GetCategory(invalidSubCategory).has_value());
}
