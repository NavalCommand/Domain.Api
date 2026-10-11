#include <NavalCommand/Units/Api/UnitInstance.h>
#include <optional>
#include <type_traits>
#include <vector>

namespace Units = NavalCommand::Units::Api;
namespace Catalog = NavalCommand::Catalog::Api;
namespace Physics = NavalCommand::Physics::Api;

static_assert(std::is_aggregate_v<Units::UnitInstance>);
static_assert(!std::is_convertible_v<Units::UnitId, Catalog::UnitTypeId>);
static_assert(std::is_same_v<decltype(Units::UnitInstance::Identity), Units::UnitId>);
static_assert(std::is_same_v<decltype(Units::KinematicsState::Position), std::optional<Physics::Position>>);
static_assert(std::is_same_v<decltype(Units::UnitInstance::Equipment), std::optional<std::vector<Units::EquipmentInstance>>>);
static_assert(std::is_same_v<decltype(Units::EquipmentInstance::Active), std::optional<bool>>);

int main()
{
	Units::UnitInstance launchedMissile;
	launchedMissile.Identity = {"sim-missile-7"};
	launchedMissile.Type = Catalog::UnitTypeId{"missile"};
	launchedMissile.Kinematics.Position = Physics::Position{{61.96}, {-10.37}, std::nullopt};
	launchedMissile.Kinematics.Speed = Physics::MetersPerSecond{250};
	// Projectile has no mandatory crew, aircraft, hull, or air-operations fields.
	return launchedMissile.Identity.Value == "sim-missile-7" && !launchedMissile.AirOperations ? 0 : 1;
}
