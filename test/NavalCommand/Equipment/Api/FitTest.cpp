#include <NavalCommand/Equipment/Api/Fit.h>
#include <gtest/gtest.h>
#include <cstdint>
#include <variant>

namespace Equipment = NavalCommand::Equipment::Api;

TEST(FitTest, StoresEquipmentAndResourceCapacitySeparatelyFromInitialInventory)
{
	Equipment::Fit fit;
	fit.TypeId = {"external-tank"};
	fit.Resource = Equipment::Fit::ResourceProvision{{"fuel"}, 300.0, 120.5};

	EXPECT_EQ(fit.TypeId.Value, "external-tank");
	ASSERT_TRUE(fit.Resource.has_value());
	EXPECT_EQ(fit.Resource->ResourceId.Value, "fuel");
	EXPECT_EQ(std::get<double>(fit.Resource->Capacity), 300.0);
	EXPECT_EQ(std::get<double>(fit.Resource->InitialInventory), 120.5);
}

TEST(FitTest, ResourceFreeSensorsHaveNoProvision)
{
	for (const char* type : {"surface-search-radar", "active-sonar", "esm"})
	{
		Equipment::Fit fit;
		fit.TypeId = {type};
		EXPECT_FALSE(fit.Resource.has_value());
	}
}

TEST(FitTest, WeaponCapacityAndZeroInitialInventoryStayPresentTogether)
{
	Equipment::Fit fit;
	fit.TypeId = {"missile-launcher"};
	fit.Resource = Equipment::Fit::ResourceProvision{{"missiles"}, std::uint64_t{8}, std::uint64_t{0}};
	ASSERT_TRUE(fit.Resource.has_value());
	EXPECT_EQ(fit.Resource->ResourceId.Value, "missiles");
	EXPECT_EQ(std::get<std::uint64_t>(fit.Resource->Capacity), 8);
	EXPECT_EQ(std::get<std::uint64_t>(fit.Resource->InitialInventory), 0);
}

TEST(FitTest, AllocatableCapacityUsesTheExistingDiscreteResourceModel)
{
	Equipment::Fit fit;
	fit.TypeId = {"fire-control-radar"};
	fit.Resource = Equipment::Fit::ResourceProvision{{"fire-control-channels"}, std::uint64_t{2}, std::uint64_t{2}};
	ASSERT_TRUE(fit.Resource.has_value());
	EXPECT_EQ(std::get<std::uint64_t>(fit.Resource->Capacity), 2);
	EXPECT_EQ(std::get<std::uint64_t>(fit.Resource->InitialInventory), 2);
}
