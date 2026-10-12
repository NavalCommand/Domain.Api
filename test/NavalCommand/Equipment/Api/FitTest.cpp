#include <NavalCommand/Equipment/Api/Fit.h>
#include <gtest/gtest.h>
#include <cstdint>
#include <variant>

namespace Equipment = NavalCommand::Equipment::Api;

TEST(FitTest, StoresEquipmentAndResourceCapacitySeparatelyFromInitialInventory)
{
	Equipment::Fit fit;
	fit.TypeId = {"external-tank"};
	fit.ResourceId = {"fuel"};
	fit.ResourceCapacity = std::uint64_t{300};
	fit.InitialInventory = std::uint64_t{120};

	EXPECT_EQ(fit.TypeId.Value, "external-tank");
	EXPECT_EQ(fit.ResourceId.Value, "fuel");
	EXPECT_EQ(std::get<std::uint64_t>(fit.ResourceCapacity), 300);
	EXPECT_EQ(std::get<std::uint64_t>(fit.InitialInventory), 120);
}
