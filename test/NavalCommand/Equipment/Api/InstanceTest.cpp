#include <NavalCommand/Equipment/Api/Instance.h>
#include <NavalCommand/Equipment/Api/Damage.h>
#include <NavalCommand/Equipment/Api/OperationalState.h>
#include <gtest/gtest.h>
#include <cstdint>
#include <variant>

namespace Equipment = NavalCommand::Equipment::Api;

TEST(EquipmentInstanceTest, ResourceFreeSensorsHaveNoInventory)
{
	for (const char* type : {"surface-search-radar", "passive-sonar", "esm"})
	{
		Equipment::Instance instance;
		instance.Type = {type};
		instance.State = Equipment::OperationalState::Active;
		instance.DamageState = Equipment::Damage::Intact;

		EXPECT_EQ(instance.Type.Value, type);
		EXPECT_EQ(instance.State, Equipment::OperationalState::Active);
		EXPECT_EQ(instance.DamageState, Equipment::Damage::Intact);
		EXPECT_FALSE(instance.Inventory.has_value());
	}
}

TEST(EquipmentInstanceTest, WeaponInventoryRemainsPresentWhenEmpty)
{
	Equipment::Instance instance;
	instance.Type = {"missile-launcher"};
	instance.State = Equipment::OperationalState::Ready;
	instance.DamageState = Equipment::Damage::Intact;
	instance.Inventory = Equipment::Instance::ResourceInventory{{"missiles"}, std::uint64_t{8}};

	ASSERT_TRUE(instance.Inventory.has_value());
	EXPECT_EQ(instance.Inventory->ResourceId.Value, "missiles");
	EXPECT_EQ(std::get<std::uint64_t>(instance.Inventory->Quantity), 8);
	instance.Inventory->Quantity = std::uint64_t{0};
	ASSERT_TRUE(instance.Inventory.has_value());
	EXPECT_EQ(instance.Inventory->ResourceId.Value, "missiles");
	EXPECT_EQ(std::get<std::uint64_t>(instance.Inventory->Quantity), 0);
}

TEST(EquipmentInstanceTest, ContinuousAndAllocatableInventoriesRetainTheirValues)
{
	Equipment::Instance tank;
	tank.Inventory = Equipment::Instance::ResourceInventory{{"fuel"}, 120.5};
	EXPECT_EQ(std::get<double>(tank.Inventory->Quantity), 120.5);
	Equipment::Instance fireControl;
	fireControl.Inventory = Equipment::Instance::ResourceInventory{{"fire-control-channels"}, std::uint64_t{2}};
	EXPECT_EQ(std::get<std::uint64_t>(fireControl.Inventory->Quantity), 2);
}
