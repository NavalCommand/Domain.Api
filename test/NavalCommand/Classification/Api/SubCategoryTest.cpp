#include <NavalCommand/Classification/Api/SubCategory.h>
#include <gtest/gtest.h>
#include <utility>

namespace Classification = NavalCommand::Classification::Api;

TEST(SubCategoryTest, MapsEveryDeclaredSubCategoryToItsExpectedCategory)
{
	using SubCategory = Classification::SubCategory;
	using Category = Classification::Category;

	const std::pair<SubCategory, Category> mappings[]{
		{SubCategory::FixedWingAircraft, Category::Aircraft},
		{SubCategory::RotaryWingAircraft, Category::Aircraft},
		{SubCategory::TiltRotorAircraft, Category::Aircraft},
		{SubCategory::CruiseMissile, Category::Missile},
		{SubCategory::BallisticMissile, Category::Missile},
		{SubCategory::AircraftCarrier, Category::SurfaceVessel},
		{SubCategory::Cruiser, Category::SurfaceVessel},
		{SubCategory::Destroyer, Category::SurfaceVessel},
		{SubCategory::Frigate, Category::SurfaceVessel},
		{SubCategory::Corvette, Category::SurfaceVessel},
		{SubCategory::PatrolVessel, Category::SurfaceVessel},
		{SubCategory::AmphibiousVessel, Category::SurfaceVessel},
		{SubCategory::AuxiliaryVessel, Category::SurfaceVessel},
		{SubCategory::MerchantVessel, Category::SurfaceVessel},
		{SubCategory::AttackSubmarine, Category::Submarine},
		{SubCategory::BallisticMissileSubmarine, Category::Submarine},
		{SubCategory::CruiseMissileSubmarine, Category::Submarine},
		{SubCategory::HeavyweightTorpedo, Category::Torpedo},
		{SubCategory::LightweightTorpedo, Category::Torpedo},
		{SubCategory::NavalMine, Category::Mine},
		{SubCategory::Noisemaker, Category::SubsurfaceDevice},
		{SubCategory::SelfPropelledAcousticDecoy, Category::SubsurfaceDevice},
		{SubCategory::Sonobuoy, Category::SurfaceDevice},
		{SubCategory::GroundVehicle, Category::LandEquipment},
		{SubCategory::SurfaceToAirMissileLauncher, Category::LandEquipment},
		{SubCategory::AntiAircraftGun, Category::LandEquipment},
		{SubCategory::Radar, Category::LandEquipment},
		{SubCategory::Airfield, Category::LandInstallation},
		{SubCategory::MilitaryInstallation, Category::LandInstallation},
		{SubCategory::CivilianInstallation, Category::LandInstallation}
	};

	for (const auto& [subCategory, expectedCategory] : mappings)
	{
		EXPECT_EQ(Classification::GetCategory(subCategory), expectedCategory);
	}
}

static_assert(Classification::GetCategory(Classification::SubCategory::Noisemaker)
	== Classification::Category::SubsurfaceDevice);
static_assert(Classification::GetCategory(Classification::SubCategory::SelfPropelledAcousticDecoy)
	== Classification::Category::SubsurfaceDevice);
static_assert(Classification::GetCategory(Classification::SubCategory::Sonobuoy)
	== Classification::Category::SurfaceDevice);
