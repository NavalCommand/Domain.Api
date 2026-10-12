#include <NavalCommand/Operations/Api/UnitState.h>
#include <NavalCommand/Equipment/Api/LoadoutId.h>
#include <NavalCommand/Equipment/Api/TypeId.h>
#include <NavalCommand/Units/Api/Instance.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <gtest/gtest.h>
#include <type_traits>
#include <variant>
#include <vector>

namespace Equipment = NavalCommand::Equipment::Api;
namespace Operations = NavalCommand::Operations::Api;
namespace Units = NavalCommand::Units::Api;

template<typename T>
concept HasCurrentActivity = requires(T value) { value.CurrentActivity; };
template<typename T>
concept HasNavigation = requires(T value) { value.Navigation; };
template<typename T>
concept HasAirOperations = requires(T value) { value.AirOperations; };

static_assert(!HasCurrentActivity<Units::Instance>);
static_assert(!HasNavigation<Units::Instance>);
static_assert(!HasAirOperations<Units::Instance>);
static_assert(std::is_same_v<decltype(Operations::UnitState::CurrentActivity), Operations::Activity>);
static_assert(std::is_same_v<decltype(Operations::UnitState::NavigationState),
	std::optional<Operations::Navigation>>);
static_assert(std::is_same_v<decltype(Operations::UnitState::AirOperationsState),
	std::optional<Operations::AirOperations>>);

TEST(UnitStateTest, StartsUnknownAndLeavesOptionalOperationsAbsent)
{
	const Operations::UnitState state;
	EXPECT_TRUE(std::holds_alternative<std::monostate>(state.CurrentActivity));
	EXPECT_FALSE(state.NavigationState.has_value());
	EXPECT_FALSE(state.AirOperationsState.has_value());
}

TEST(UnitStateTest, KeepsNavigationAndAirOperationsInOperationsState)
{
	Operations::UnitState state;
	state.NavigationState.emplace();
	state.NavigationState->PlannedRoute.push_back({{}, "patrol point"});
	state.AirOperationsState.emplace();
	Operations::AircraftInventoryEntry aircraft;
	aircraft.Type = Units::TypeId{"rotorcraft"};
	aircraft.Squadron = "flight-a";
	aircraft.UnreservedCount = 2;
	aircraft.Loadouts = std::vector<Equipment::LoadoutId>{{"patrol"}};
	state.AirOperationsState->Inventory = std::vector<Operations::AircraftInventoryEntry>{aircraft};

	ASSERT_TRUE(state.NavigationState.has_value());
	EXPECT_EQ(state.NavigationState->PlannedRoute.front().Label, "patrol point");
	ASSERT_TRUE(state.AirOperationsState->Inventory.has_value());
	EXPECT_EQ(state.AirOperationsState->Inventory->front().Type.Value, "rotorcraft");
	EXPECT_EQ(state.AirOperationsState->Inventory->front().UnreservedCount, 2);
}
