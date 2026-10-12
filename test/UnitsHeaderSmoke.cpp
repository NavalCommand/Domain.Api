#include <NavalCommand/Equipment/Api/Instance.h>
#include <NavalCommand/Factions/Api/Id.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Units/Api/Instance.h>
#include <NavalCommand/Units/Api/Type.h>
#include <optional>
#include <type_traits>

namespace Equipment = NavalCommand::Equipment::Api;
namespace Factions = NavalCommand::Factions::Api;
namespace Physics = NavalCommand::Physics::Api;
namespace Units = NavalCommand::Units::Api;

static_assert(std::is_aggregate_v<Units::Instance>);
static_assert(std::is_same_v<decltype(Units::Instance::Identity), Units::Id>);
static_assert(std::is_same_v<decltype(Units::Instance::Type), Units::TypeId>);
static_assert(std::is_same_v<decltype(Units::Instance::Aircraft), std::optional<Units::AircraftInstance>>);

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
	carrier.Aircraft.emplace();
	carrier.Aircraft->Airborne = true;

	return carrier.Identity.Value == "unit-carrier" && carrier.Equipment.size() == 1 &&
		carrier.Aircraft->Airborne.value_or(false) ? 0 : 1;
}
