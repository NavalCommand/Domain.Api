#include <NavalCommand/Equipment/Api/LoadoutId.h>
#include <NavalCommand/Equipment/Api/TypeId.h>
#include <NavalCommand/Observations/Api/Id.h>
#include <NavalCommand/Operations/Api/Activity.h>
#include <NavalCommand/Operations/Api/AirOperations.h>
#include <NavalCommand/Operations/Api/AircraftInventoryEntry.h>
#include <NavalCommand/Operations/Api/IProvider.h>
#include <NavalCommand/Operations/Api/UnitState.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Physics/Api/Radians.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <NavalCommand/Units/Api/Id.h>
#include <NavalCommand/Units/Api/Instance.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <optional>
#include <type_traits>
#include <variant>
#include <vector>

namespace Equipment = NavalCommand::Equipment::Api;
namespace Observations = NavalCommand::Observations::Api;
namespace Operations = NavalCommand::Operations::Api;
namespace Physics = NavalCommand::Physics::Api;
namespace Units = NavalCommand::Units::Api;
namespace Uncertainty = NavalCommand::Uncertainty::Api;

using ExpectedTarget = std::variant<
	std::monostate,
	Observations::Id,
	Physics::Position,
	Physics::Radians>;

static_assert(std::is_same_v<decltype(Operations::EngagingWith::Target), ExpectedTarget>);
static_assert(std::is_same_v<
	decltype(Operations::EvasiveManeuvers::DangerSource),
	Uncertainty::Exact<Observations::Id>>);
static_assert(!std::is_same_v<Units::Id, Observations::Id>);
static_assert(std::is_abstract_v<Operations::IProvider>);

template<typename T>
concept HasCurrentActivity = requires(T value)
{
	value.CurrentActivity;
};

template<typename T>
concept HasNavigation = requires(T value)
{
	value.Navigation;
};

template<typename T>
concept HasAirOperations = requires(T value)
{
	value.AirOperations;
};

static_assert(!HasCurrentActivity<Units::Instance>);
static_assert(!HasNavigation<Units::Instance>);
static_assert(!HasAirOperations<Units::Instance>);

int main()
{
	Operations::UnitState state;
	if (!std::holds_alternative<std::monostate>(state.CurrentActivity) ||
		state.NavigationState.has_value() ||
		state.AirOperationsState.has_value())
	{
		return 1;
	}

	const Observations::Id contactId{"contact-1"};
	Operations::EngagingWith engagement;
	engagement.Target = contactId;
	engagement.EquipmentType = Equipment::TypeId{"surface-search-radar"};
	state.CurrentActivity = engagement;

	state.NavigationState.emplace();
	state.NavigationState->PlannedRoute.push_back({{}, "patrol point"});

	state.AirOperationsState.emplace();
	Operations::AircraftInventoryEntry aircraft;
	aircraft.Type = Units::TypeId{"rotorcraft"};
	aircraft.Squadron = "flight-a";
	aircraft.UnreservedCount = 2;
	aircraft.Loadouts = std::vector<Equipment::LoadoutId>{{"patrol"}};
	state.AirOperationsState->Inventory = std::vector<Operations::AircraftInventoryEntry>{aircraft};

	const auto &currentEngagement = std::get<Operations::EngagingWith>(state.CurrentActivity);
	const auto &storedContact = std::get<Observations::Id>(currentEngagement.Target);
	const auto &storedAircraft = state.AirOperationsState->Inventory->front();

	return storedContact.Value == "contact-1" &&
		state.NavigationState->PlannedRoute.front().Label == "patrol point" &&
		storedAircraft.Type.Value == "rotorcraft" &&
		storedAircraft.UnreservedCount == 2 ? 0 : 1;
}
