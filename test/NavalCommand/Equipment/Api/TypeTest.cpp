#include <NavalCommand/Equipment/Api/Type.h>
#include <NavalCommand/Equipment/Api/LoadoutId.h>
#include <gtest/gtest.h>
#include <type_traits>

namespace Equipment = NavalCommand::Equipment::Api;

static_assert(!std::is_same_v<Equipment::TypeId, Equipment::LoadoutId>);

TEST(EquipmentTypeTest, HasATypeIdentity)
{
	Equipment::Type type;
	type.Id = {"surface-search-radar"};
	EXPECT_EQ(type.Id.Value, "surface-search-radar");
}
