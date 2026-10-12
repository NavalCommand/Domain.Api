#include <NavalCommand/Equipment/Api/Instance.h>
#include <NavalCommand/Factions/Api/Id.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Physics/Api/Radians.h>
#include <NavalCommand/Units/Api/Activity.h>
#include <NavalCommand/Units/Api/AircraftInventoryEntry.h>
#include <NavalCommand/Units/Api/Instance.h>
#include <NavalCommand/Units/Api/Type.h>
#include <optional>
#include <type_traits>
#include <variant>
#include <vector>

namespace Equipment = NavalCommand::Equipment::Api;
namespace Factions = NavalCommand::Factions::Api;
namespace Physics = NavalCommand::Physics::Api;
namespace Units = NavalCommand::Units::Api;

static_assert(std::is_aggregate_v<Units::Instance>);
static_assert(std::is_same_v<decltype(Units::Instance::Identity), Units::Id>);
static_assert(std::is_same_v<decltype(Units::Instance::Type), Units::TypeId>);
static_assert(std::is_same_v<decltype(Units::EngagingWith::Target),
	std::variant<std::monostate, Units::Id, Physics::Position, Physics::Radians>>);
static_assert(std::is_same_v<decltype(Units::EvasiveManeuvers::DangerSource),
	NavalCommand::Uncertainty::Api::Exact<Units::Id>>);

int main()
{
	Units::Instance carrier;
	carrier.Identity = {"unit-carrier"};
	carrier.Name = "Example carrier";
	carrier.Type = {"carrier"};
	carrier.Faction = Factions::Id{"blue"};
	carrier.Kinematics.Position = Physics::Position{{61.96}, {-10.37}, {0}};

	Equipment::Instance radar;
	radar.Type = {"surface-search-radar"};
	carrier.Equipment.push_back(radar);

	Units::EngagingWith engagement;
	engagement.Target = Units::Id{"unit-target"};
	engagement.EquipmentType = {"surface-search-radar"};
	carrier.CurrentActivity = engagement;

	Units::AircraftInventoryEntry aircraft;
	aircraft.Type = {"rotorcraft"};
	aircraft.Squadron = "flight-a";
	aircraft.UnreservedCount = 2;
	aircraft.Loadouts = std::vector<Equipment::LoadoutId>{{"patrol"}};
	carrier.AirOperations.emplace();
	carrier.AirOperations->Inventory = std::vector<Units::AircraftInventoryEntry>{aircraft};

	const auto& currentEngagement = std::get<Units::EngagingWith>(carrier.CurrentActivity);
	return carrier.Identity.Value == "unit-carrier" && carrier.Equipment.size() == 1 &&
		std::get<Units::Id>(currentEngagement.Target).Value == "unit-target" &&
		carrier.AirOperations->Inventory->front().Type.Value == "rotorcraft" ? 0 : 1;
}
