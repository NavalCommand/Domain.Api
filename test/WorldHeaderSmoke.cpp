#include <NavalCommand/World/Api/Catalog.h>
#include <NavalCommand/World/Api/View.h>
#include <stdexcept>
#include <type_traits>

using namespace NavalCommand;
using namespace World::Api;
using Orders::Api::OwnUnitId;

static void Require(bool condition) {
	if (!condition) {
		throw std::runtime_error("Domain composition assertion failed");
	}
}

int main() {
	static_assert(std::is_aggregate_v<UnitInstance>);
	static_assert(!std::is_assignable_v<Orders::Api::OwnUnitId &, TrackId>);
	using Equipment = ObservedCollection<EquipmentInstance>;
	Require(Equipment{}.GetCoverage() == Equipment::Coverage::Unknown);
	Require(Equipment{Equipment::Coverage::Complete, {}}.Items().empty());
	Require(Equipment{Equipment::Coverage::Partial, {EquipmentInstance{}}}.Items().size() == 1);
	Require(Equipment{Equipment::Coverage::Partial, {}}.GetCoverage() == Equipment::Coverage::Partial);
	bool invalidRejected = false;
	try {
		Equipment invalid{Equipment::Coverage::Unknown, {EquipmentInstance{}}};
	} catch (const std::invalid_argument &) {
		invalidRejected = true;
	}
	Require(invalidRejected);
	Require(!Knowledge<double>{}.HasValue());
	Require(Knowledge<double>::Known(0).Value() == 0);
	bool unknownRejected = false;
	try {
		Knowledge<double>{}.Value();
	} catch (const std::logic_error &) {
		unknownRejected = true;
	}
	Require(unknownRejected);

	using Capability = EquipmentCapability;
	using Operation = EquipmentOperation;
	using Resource = ResourceQuantity;
	Catalog catalog;
	catalog.Revision = "synthetic-scenario-v1";
	EquipmentType missile{"missile",
						  {{Capability::Damage{}}},
						  {{"launch",
							0,
							{Operation::TargetInput::Track, Operation::TargetInput::Location},
							Operation::Action::Launch,
							Operation::Duration::OneShot,
							{{Resource::Kind::Ammunition, 1}},
							{Operation::Mode::Guided}}}};
	EquipmentType radar{"radar",
						{{Capability::Sensing{Capability::SensingMode::Radar}}},
						{{"scan", 0, {Operation::TargetInput::None}, Operation::Action::Activate, Operation::Duration::Continuous, {}, {Operation::Mode::Active}}}};
	EquipmentType jammer{"jammer",
						 {{Capability::Jamming{}}},
						 {{"jam",
						   0,
						   {Operation::TargetInput::Track, Operation::TargetInput::Location},
						   Operation::Action::Activate,
						   Operation::Duration::Continuous,
						   {{Resource::Kind::JamChannels, 1}},
						   {Operation::Mode::Active}}}};
	EquipmentType chaff{"chaff",
						{{Capability::Deception{}}},
						{{"deploy", 0, {Operation::TargetInput::None}, Operation::Action::Deploy, Operation::Duration::OneShot, {{Resource::Kind::DeploymentCharges, 1}}}}};
	EquipmentType buoy{"sonobuoy",
					   {{Capability::Sensing{Capability::SensingMode::Sonar}}},
					   {{"deploy",
						 0,
						 {Operation::TargetInput::Area, Operation::TargetInput::Location},
						 Operation::Action::Deploy,
						 Operation::Duration::OneShot,
						 {{Resource::Kind::DeploymentCharges, 1}}},
						{"listen", 0, {Operation::TargetInput::None}, Operation::Action::Activate, Operation::Duration::Continuous, {}, {Operation::Mode::Passive}}}};
	EquipmentType tank{"tank", {{Capability::Storage{}}}, {{"jettison", 0, {Operation::TargetInput::None}, Operation::Action::Jettison, Operation::Duration::OneShot, {}}}};
	catalog.EquipmentTypes = {missile, radar, jammer, chaff, buoy, tank};
	UnitType helicopter{
		"helicopter",
		{PlatformDescription::Helicopter{}},
		{{"strike", {{"radar", {}}, {"missile", {{Resource::Kind::Ammunition, 4}}}, {"chaff", {{Resource::Kind::DeploymentCharges, 20}}}}},
		 {"patrol",
		  {{"radar", {}}, {"sonobuoy", {{Resource::Kind::DeploymentCharges, 8}}}, {"tank", {{Resource::Kind::FuelLiters, 300}}}, {"jammer", {{Resource::Kind::JamChannels, 2}}}}}}};
	catalog.UnitTypes.push_back(helicopter);
	Require(catalog.EquipmentTypes.size() == 6);
	Require(catalog.UnitTypes[0].Loadouts.size() == 2);
	Require(std::holds_alternative<PlatformDescription::Helicopter>(helicopter.Platform.Description));
	for (const auto &unitType : catalog.UnitTypes) {
		for (const auto &loadout : unitType.Loadouts) {
			for (const auto &fit : loadout.Equipment) {
				bool resolved = false;
				for (const auto &type : catalog.EquipmentTypes) {
					resolved = resolved || type.Id == fit.EquipmentTypeId;
				}
				Require(resolved);
			}
		}
	}
	Require(helicopter.Loadouts[0].Equipment[0].EquipmentTypeId == helicopter.Loadouts[1].Equipment[0].EquipmentTypeId);
	for (const auto &type : catalog.EquipmentTypes) {
		for (const auto &operation : type.Operations) {
			Require(operation.CapabilityIndex < type.Capabilities.size());
		}
	}
	Require(missile.Operations[0].SupportedModes[0] == Operation::Mode::Guided);
	Require(radar.Operations[0].Costs.empty());
	Require(jammer.Operations[0].Costs[0].Resource == Resource::Kind::JamChannels);
	Require(chaff.Operations[0].AcceptedTargets[0] == Operation::TargetInput::None);
	Require(buoy.Operations.size() == 2 && buoy.Operations[1].OperationDuration == Operation::Duration::Continuous);
	Require(std::holds_alternative<Capability::Storage>(tank.Capabilities[0].Behavior));

	UnitInstance own;
	own.Identity = OwnUnitId{"same-text"};
	own.Display.Name = Knowledge<std::string>::Known("Aircraft");
	own.Kinematics.Position = Knowledge<PositionObservation>::Known({{0, 0, 0}});
	own.Kinematics.SpeedMetersPerSecond = Knowledge<double>::Known(0);
	own.Navigation = NavigationState{Knowledge<bool>::Known(true), Knowledge<std::vector<Orders::Api::RoutePoint>>::Known({{1, 2, "destination"}})};
	own.OrderEligibility = OrderEligibilityState{{ObservedCollection<Orders::Api::Eligibility>::Coverage::Complete, {{"replace_route", Orders::Api::Availability::Executable}}}};
	own.Aircraft = AircraftState{Knowledge<bool>::Known(false)};
	own.Observation.SampledAtSeconds = Knowledge<double>::Known(42);
	EquipmentInstance currentMissile;
	currentMissile.TypeId = Knowledge<std::string>::Known("missile");
	currentMissile.Resources.push_back({Resource::Kind::Ammunition, Knowledge<double>::Known(0)});
	own.Equipment = {Equipment::Coverage::Complete, {currentMissile}};
	UnitInstance contact;
	contact.Identity = TrackId{"same-text"};
	contact.Display.TypeId = Knowledge<std::string>::Known("helicopter");
	contact.Kinematics.Position = Knowledge<PositionObservation>::Estimated({{1, 2, {}}}, "observer");
	contact.Observation.Provenance = Knowledge<std::string>::Known("observer");
	View view;
	view.Instances = {own, contact};
	Require(std::holds_alternative<OwnUnitId>(view.Instances[0].Identity));
	Require(std::holds_alternative<TrackId>(view.Instances[1].Identity));
	Require(!view.Instances[1].OrderEligibility);
	Require(view.Instances[1].Equipment.GetCoverage() == Equipment::Coverage::Unknown);
	Require(!view.Instances[0].Aircraft->Airborne.Value());
	Require(!view.Instances[1].Aircraft);
	Require(currentMissile.Resources[0].Amount.IsKnown());
	Require(EquipmentInstance{}.Resources.empty()); // Resource does not apply; not an unknown ammunition count.
	Require(!EquipmentInstance::Resource{Resource::Kind::Ammunition, {}}.Amount.HasValue());
	return 0;
}
