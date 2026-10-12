#include <NavalCommand/Equipment/Api/Instance.h>
#include <NavalCommand/Equipment/Api/Damage.h>
#include <NavalCommand/Equipment/Api/OperationalState.h>
#include <gtest/gtest.h>
#include <cstdint>
#include <variant>

namespace Equipment = NavalCommand::Equipment::Api;

TEST(EquipmentInstanceTest, StoresOperationalAndExpendableState)
{
	Equipment::Instance instance;
	instance.Type = {"surface-search-radar"};
	instance.State = Equipment::OperationalState::Ready;
	instance.DamageState = Equipment::Damage::Intact;
	instance.ExpendableResourceId = {"fuel"};
	instance.ExpendableResourceValue = std::uint64_t{120};

	EXPECT_EQ(instance.Type.Value, "surface-search-radar");
	EXPECT_EQ(instance.State, Equipment::OperationalState::Ready);
	EXPECT_EQ(instance.DamageState, Equipment::Damage::Intact);
	EXPECT_EQ(std::get<std::uint64_t>(instance.ExpendableResourceValue), 120);
}
