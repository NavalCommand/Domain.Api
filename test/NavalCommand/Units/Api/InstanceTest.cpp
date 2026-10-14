#include <NavalCommand/Units/Api/Instance.h>
#include <NavalCommand/Equipment/Api/Instance.h>
#include <NavalCommand/Factions/Api/Id.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <gtest/gtest.h>
#include <optional>
#include <type_traits>

namespace Equipment = NavalCommand::Equipment::Api;
namespace Factions = NavalCommand::Factions::Api;
namespace Physics = NavalCommand::Physics::Api;
namespace Units = NavalCommand::Units::Api;

static_assert(std::is_aggregate_v<Units::Instance>);
static_assert(std::is_same_v<decltype(Units::Instance::Identity), Units::Id>);
static_assert(std::is_same_v<decltype(Units::Instance::Type), Units::TypeId>);
static_assert(std::is_same_v<decltype(Units::Instance::CurrentLoadout), Equipment::LoadoutId>);
static_assert(std::is_same_v<decltype(Units::Instance::IsDestroyed), bool>);
static_assert(std::is_same_v<decltype(Units::Instance::Aircraft), std::optional<Units::AircraftInstance>>);

TEST(UnitInstanceTest, ContainsAuthoritativeStateWithoutOperationsProjection)
{
	Units::Instance carrier;
	carrier.Identity = {"unit-carrier"};
	carrier.Name = "Example carrier";
	carrier.Type = {"carrier"};
	carrier.CurrentLoadout = Equipment::LoadoutId{"standard"};
	carrier.IsDestroyed = true;
	carrier.Faction = Factions::Id{"blue"};
	carrier.Kinematics.Position = Physics::Position{{61.96}, {-10.37}, {0}};
	carrier.Equipment.push_back(Equipment::Instance{});
	carrier.Aircraft.emplace();
	carrier.Aircraft->Airborne = true;

	EXPECT_EQ(carrier.Identity.Value, "unit-carrier");
	EXPECT_EQ(carrier.CurrentLoadout.Value, "standard");
	EXPECT_TRUE(carrier.IsDestroyed);
	EXPECT_EQ(carrier.Equipment.size(), 1);
	ASSERT_TRUE(carrier.Aircraft.has_value());
	EXPECT_TRUE(carrier.Aircraft->Airborne.value_or(false));
}

TEST(UnitInstanceTest, HasCurrentLoadoutIdentityEvenForEmptyConfigurations)
{
	Units::Instance unit;
	unit.CurrentLoadout = Equipment::LoadoutId{"empty"};
	EXPECT_EQ(unit.CurrentLoadout.Value, "empty");
}
