#include <NavalCommand/Equipment/Api/Operation.h>
#include <gtest/gtest.h>
#include <cstdint>
#include <variant>

namespace Equipment = NavalCommand::Equipment::Api;

TEST(EquipmentOperationTest, EnablingAResourceFreeSensorHasNoRequirement)
{
	Equipment::Operation operation;
	operation.AcceptedTargets = Equipment::Operation::TargetInput::NoTarget;
	operation.Invocation = Equipment::Operation::Action::SetActive;
	EXPECT_EQ(operation.Invocation, Equipment::Operation::Action::SetActive);
	EXPECT_FALSE(operation.Resource.has_value());
}

TEST(EquipmentOperationTest, WeaponUseConsumesTheSpecifiedResource)
{
	Equipment::Operation operation;
	operation.AcceptedTargets = Equipment::Operation::TargetInput::Unit;
	operation.Invocation = Equipment::Operation::Action::Use;
	operation.Resource = Equipment::Operation::ResourceRequirement{Equipment::Operation::ResourceUse::Consume, {"missiles"}, std::uint64_t{1}};
	ASSERT_TRUE(operation.Resource.has_value());
	EXPECT_EQ(operation.Resource->Use, Equipment::Operation::ResourceUse::Consume);
	EXPECT_EQ(operation.Resource->ResourceId.Value, "missiles");
	EXPECT_EQ(std::get<std::uint64_t>(operation.Resource->Amount), 1);
}

TEST(EquipmentOperationTest, FireControlReservesAnAllocatableResource)
{
	Equipment::Operation operation;
	operation.AcceptedTargets = Equipment::Operation::TargetInput::Unit;
	operation.Invocation = Equipment::Operation::Action::Use;
	operation.Resource = Equipment::Operation::ResourceRequirement{Equipment::Operation::ResourceUse::Reserve, {"fire-control-channels"}, std::uint64_t{1}};
	ASSERT_TRUE(operation.Resource.has_value());
	EXPECT_EQ(operation.Resource->Use, Equipment::Operation::ResourceUse::Reserve);
	EXPECT_EQ(operation.Resource->ResourceId.Value, "fire-control-channels");
	EXPECT_EQ(std::get<std::uint64_t>(operation.Resource->Amount), 1);
}

TEST(EquipmentOperationTest, AZeroRequirementRemainsDistinctFromNoResource)
{
	Equipment::Operation operation;
	operation.AcceptedTargets = Equipment::Operation::TargetInput::NoTarget;
	operation.Resource = Equipment::Operation::ResourceRequirement{Equipment::Operation::ResourceUse::Consume, {"fuel"}, 0.0};
	ASSERT_TRUE(operation.Resource.has_value());
	EXPECT_EQ(operation.Resource->ResourceId.Value, "fuel");
	EXPECT_EQ(std::get<double>(operation.Resource->Amount), 0.0);
	operation.Resource.reset();
	EXPECT_FALSE(operation.Resource.has_value());
}
