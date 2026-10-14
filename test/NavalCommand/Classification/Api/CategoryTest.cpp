#include <NavalCommand/Classification/Api/Category.h>
#include <gtest/gtest.h>
#include <utility>

namespace Classification = NavalCommand::Classification::Api;

TEST(CategoryTest, MapsEveryDeclaredCategoryToItsExpectedDimension)
{
	using Category = Classification::Category;
	using Dimension = Classification::Dimension;

	const std::pair<Category, Dimension> mappings[]{
		{Category::Aircraft, Dimension::Air},
		{Category::Missile, Dimension::Air},
		{Category::SurfaceVessel, Dimension::SeaSurface},
		{Category::Submarine, Dimension::SeaSubsurface},
		{Category::Torpedo, Dimension::SeaSubsurface},
		{Category::Mine, Dimension::SeaSubsurface},
		{Category::LandEquipment, Dimension::Land},
		{Category::LandInstallation, Dimension::Land},
		{Category::LandUnit, Dimension::Land},
		{Category::SpaceObject, Dimension::Space},
		{Category::SurfaceDevice, Dimension::SeaSurface},
		{Category::SubsurfaceDevice, Dimension::SeaSubsurface},
		{Category::SeaAnimal, Dimension::SeaSubsurface},
		{Category::Other, Dimension::Other}
	};

	for (const auto& [category, expectedDimension] : mappings)
	{
		EXPECT_EQ(Classification::GetDimension(category), expectedDimension);
	}
}

static_assert(Classification::GetDimension(Classification::Category::SurfaceDevice)
	== Classification::Dimension::SeaSurface);
static_assert(Classification::GetDimension(Classification::Category::SubsurfaceDevice)
	== Classification::Dimension::SeaSubsurface);
