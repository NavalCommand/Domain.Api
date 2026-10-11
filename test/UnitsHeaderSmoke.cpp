#include <NavalCommand/Units/Api/UnitInstance.h>
#include <stdexcept>
#include <type_traits>

namespace Units = NavalCommand::Units::Api;
namespace Catalog = NavalCommand::Catalog::Api;
namespace Physics = NavalCommand::Physics::Api;
namespace Uncertainty = NavalCommand::Uncertainty::Api;

static void Require(bool condition)
{
	if (!condition)
	{
		throw std::runtime_error("Unit observation assertion failed");
	}
}

int main()
{
	static_assert(std::is_aggregate_v<Units::UnitInstance>);
	static_assert(!std::is_convertible_v<Units::UnitId, Catalog::UnitTypeId>);
	Units::UnitInstance own;
	own.Identity = {"session-observation-1"};
	own.Display.Name = Uncertainty::Knowledge<std::string>::Known("Own helicopter");
	own.Kinematics.Position = Uncertainty::Knowledge<Units::PositionObservation>::Known({{{0}, {0}, Physics::Meters{0}}, std::nullopt});
	own.Kinematics.Speed = Uncertainty::Knowledge<Physics::MetersPerSecond>::Known({0});
	own.Kinematics.Heading = Uncertainty::Knowledge<Physics::Radians>::Known({1});
	own.Kinematics.CourseOverGround = Uncertainty::Knowledge<Physics::Radians>::Known({2});
	own.Aircraft = Units::AircraftState{Uncertainty::Knowledge<bool>::Known(false)};
	own.Navigation = Units::NavigationState{Uncertainty::Knowledge<std::vector<Units::RoutePoint>>::Known({})};
	Require(own.Navigation->PlannedRoute.IsKnown() && own.Navigation->PlannedRoute.Value().empty());
	Require(!Units::NavigationState{}.PlannedRoute.HasValue());
	Require(own.Kinematics.Heading.Value().Value != own.Kinematics.CourseOverGround.Value().Value);
	Require(own.Kinematics.Speed.Value().Value == 0 && !own.Aircraft->Airborne.Value());

	Units::UnitInstance contact;
	contact.Identity = {"session-observation-2"};
	contact.Kinematics.Position = Uncertainty::Knowledge<Units::PositionObservation>::Estimated({{{1}, {2}, std::nullopt}, std::nullopt}, "visible contact estimate");
	Require(!contact.Observation.MeasuredAt.HasValue());
	Require(!contact.Kinematics.Heading.HasValue() && !contact.Kinematics.CourseOverGround.HasValue());
	Require(!contact.AirOperations && !contact.Aircraft);

	using Equipment = Uncertainty::ObservedCollection<Units::EquipmentInstance>;
	using Resources = Uncertainty::ObservedCollection<Units::EquipmentInstance::Resource>;
	Require(contact.Equipment.GetCoverage() == Equipment::Coverage::Unknown);
	Units::EquipmentInstance missile;
	missile.TypeId = Uncertainty::Knowledge<Catalog::EquipmentTypeId>::Known({"missile"});
	Require(missile.Resources.GetCoverage() == Resources::Coverage::Unknown);
	missile.Resources = {Resources::Coverage::Partial, {{{"missile-rounds"}, Uncertainty::Knowledge<Catalog::ResourceValue>::Known(std::uint64_t{0})}}};
	Require(missile.Resources.GetCoverage() == Resources::Coverage::Partial);
	Require(std::get<std::uint64_t>(missile.Resources.Items()[0].Amount.Value()) == 0);
	Require(!Units::EquipmentInstance::Resource{{"missile-rounds"}, {}}.Amount.HasValue());
	missile.Resources = {Resources::Coverage::Complete, {}};
	Require(missile.Resources.Items().empty());
	own.Equipment = {Equipment::Coverage::Complete, {std::move(missile)}};
	Require(own.Equipment.GetCoverage() == Equipment::Coverage::Complete);

	Units::UnitInstance carrier;
	carrier.Identity = {"session-observation-3"};
	carrier.AirOperations.emplace();
	using Inventory = Uncertainty::ObservedCollection<Units::AircraftInventoryEntry>;
	Require(carrier.AirOperations->Inventory.GetCoverage() == Inventory::Coverage::Unknown);
	carrier.AirOperations->Inventory = {Inventory::Coverage::Partial, {{{"helicopter"}, "squadron", Uncertainty::Knowledge<std::uint32_t>::Known(0), {{"patrol"}}}}};
	carrier.AirOperations->PendingOperations = Uncertainty::Knowledge<std::uint32_t>::Known(0);
	carrier.AirOperations->ReservedCount = Uncertainty::Knowledge<std::uint32_t>::Known(2);
	carrier.AirOperations->CooldownCount = Uncertainty::Knowledge<std::uint32_t>::Known(1);
	carrier.AirOperations->MeasuredAt = Uncertainty::Knowledge<Physics::Seconds>::Known({40});
	Require(carrier.AirOperations->Inventory.Items()[0].UnreservedCount.IsKnown());
	Require(carrier.AirOperations->Inventory.Items()[0].UnreservedCount.Value() == 0);
	Require(!carrier.AirOperations->OnboardCount.HasValue());
	Require(!Units::AircraftInventoryEntry{}.UnreservedCount.HasValue());
	Require(carrier.AirOperations->ReservedCount.Value() == 2 && carrier.AirOperations->CooldownCount.Value() == 1);
	carrier.AirOperations->Inventory = {Inventory::Coverage::Complete, {}};
	Require(carrier.AirOperations->Inventory.GetCoverage() == Inventory::Coverage::Complete);
	return 0;
}
