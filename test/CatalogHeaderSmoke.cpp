#include <NavalCommand/Catalog/Api/Catalog.h>
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <cstdint>
#include <optional>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <variant>
#include <vector>

namespace Catalog = NavalCommand::Catalog::Api;
static void Require(bool condition)
{
	if (!condition)
	{
		throw std::runtime_error("Catalog semantic assertion failed");
	}
}

static Catalog::ResourceQuantity Count(const char* resource, std::uint64_t count)
{
	return {{resource}, count};
}

static Catalog::EquipmentFit Fit(const char* equipment, std::vector<Catalog::ResourceQuantity> capacity, std::vector<Catalog::ResourceQuantity> initial)
{
	return {{equipment}, std::move(capacity), std::move(initial)};
}

int main()
{
	static_assert(!std::is_assignable_v<Catalog::UnitTypeId&, Catalog::EquipmentTypeId>);
	static_assert(!std::is_assignable_v<Catalog::LoadoutId&, Catalog::ResourceId>);
	using Effect = Catalog::EquipmentEffect;
	using Operation = Catalog::EquipmentOperation;
	using Definition = Catalog::ResourceDefinition;

	Catalog::Catalog catalog;
	catalog.Revision = "synthetic-resolved-session";
	catalog.Resources = {
		{{"missile-rounds"}, Definition::NumericRepresentation::Discrete, Definition::MeasurementUnit::Count, Definition::AccountingSemantics::Consumable},
		{{"chaff-bundles"}, Definition::NumericRepresentation::Discrete, Definition::MeasurementUnit::Count, Definition::AccountingSemantics::Consumable},
		{{"sonobuoys"}, Definition::NumericRepresentation::Discrete, Definition::MeasurementUnit::Count, Definition::AccountingSemantics::Consumable},
		{{"jam-channels"}, Definition::NumericRepresentation::Discrete, Definition::MeasurementUnit::Count, Definition::AccountingSemantics::Allocatable},
		{{"fuel"}, Definition::NumericRepresentation::Continuous, Definition::MeasurementUnit::CubicMeters, Definition::AccountingSemantics::Consumable}};

	Catalog::EquipmentType missile{
		{"missile"},
		{{Effect::Damage{Effect::Damage::Guidance::Autonomous}}},
		{{"fire", {Operation::TargetInput::Unit, Operation::TargetInput::Location}, Operation::Action::Use, {{Count("missile-rounds", 1), Operation::ResourceUse::Consume}}}}};
	Catalog::EquipmentType radar{
		{"radar"},
		{{Effect::Sensing{Effect::SensingMode::Radar, NavalCommand::Physics::Api::Meters{100000}}}},
		{{"scan", {}, Operation::Action::SetActive, {}}}};
	Catalog::EquipmentType jammer{
		{"jammer"},
		{{Effect::Jamming{}}},
		{{"jam", {Operation::TargetInput::Unit, Operation::TargetInput::Bearing}, Operation::Action::SetActive, {{Count("jam-channels", 1), Operation::ResourceUse::Reserve}}}}};
	Catalog::EquipmentType chaff{
		{"chaff"}, {{Effect::Deception{}}},
		{{"release", {}, Operation::Action::Use, {{Count("chaff-bundles", 1), Operation::ResourceUse::Consume}}}}};
	Catalog::EquipmentType sonobuoy{
		{"sonobuoy"}, {{Effect::Sensing{Effect::SensingMode::Sonar, std::nullopt}}, {Effect::Communication{}}},
		{{"deploy", {Operation::TargetInput::Area, Operation::TargetInput::Location}, Operation::Action::Use, {{Count("sonobuoys", 1), Operation::ResourceUse::Consume}}},
		 {"listen", {}, Operation::Action::SetActive, {}}}};
	Catalog::EquipmentType tank{{"external-tank"}, {{Effect::Storage{}}}, {{"jettison", {}, Operation::Action::Use, {}}}};
	catalog.EquipmentTypes = {missile, radar, jammer, chaff, sonobuoy, tank};

	Catalog::ResourceQuantity tankCapacity{{"fuel"}, 0.3};
	Catalog::UnitType helicopter;
	helicopter.Id = {"helicopter"};
	helicopter.Platform = Catalog::PlatformDescription{Catalog::PlatformDescription::Kind::RotaryWingAircraft};
	helicopter.Loadouts = {
		{{"strike"},
		 {Fit("radar", {}, {}),
		  Fit("missile", {Count("missile-rounds", 4)}, {Count("missile-rounds", 4)}),
		  Fit("chaff", {Count("chaff-bundles", 20)}, {Count("chaff-bundles", 20)})}},
		{{"patrol"},
		 {Fit("radar", {}, {}),
		  Fit("sonobuoy", {Count("sonobuoys", 8)}, {Count("sonobuoys", 8)}),
		  Fit("external-tank", {tankCapacity}, {tankCapacity}),
		  Fit("jammer", {Count("jam-channels", 2)}, {Count("jam-channels", 0)})}}};
	catalog.UnitTypes.push_back(helicopter);
	Catalog::UnitType launchedProjectileType;
	launchedProjectileType.Id = {"launched-projectile"};
	Require(!launchedProjectileType.Platform.has_value());
	catalog.UnitTypes.push_back(launchedProjectileType);
	Require(catalog.EquipmentTypes.size() == 6);
	Require(catalog.UnitTypes[0].Loadouts.size() == 2);
	Require(helicopter.Platform->Category == Catalog::PlatformDescription::Kind::RotaryWingAircraft);
	Require(helicopter.Loadouts[0].Equipment[0].TypeId == helicopter.Loadouts[1].Equipment[0].TypeId);

	for (const auto& loadout : helicopter.Loadouts)
	{
		for (const auto& fit : loadout.Equipment)
		{
			bool typeResolved = false;
			for (const auto& type : catalog.EquipmentTypes)
			{
				typeResolved = typeResolved || type.Id == fit.TypeId;
			}
			Require(typeResolved);
			for (const auto* relationship : {&fit.Capacity, &fit.InitialInventory})
			{
				for (const auto& quantity : *relationship)
				{
					bool resourceResolved = false;
					for (const auto& definition : catalog.Resources)
					{
						if (definition.Id == quantity.Resource)
						{
							resourceResolved = true;
							Require((definition.Representation == Definition::NumericRepresentation::Discrete) == std::holds_alternative<std::uint64_t>(quantity.Amount));
						}
					}
					Require(resourceResolved);
				}
			}
		}
	}
	Require(std::get<Effect::Damage>(missile.Effects[0].Behavior).ProjectileGuidance == Effect::Damage::Guidance::Autonomous);
	Require(missile.Operations[0].Invocation == Operation::Action::Use);
	Require(missile.Operations[0].Costs[0].Use == Operation::ResourceUse::Consume);
	Require(radar.Operations[0].Invocation == Operation::Action::SetActive && radar.Operations[0].AcceptedTargets.empty());
	Require(jammer.Operations[0].Costs[0].Use == Operation::ResourceUse::Reserve);
	Require(catalog.Resources[3].Accounting == Definition::AccountingSemantics::Allocatable);
	Require(chaff.Operations[0].AcceptedTargets.empty());
	Require(sonobuoy.Effects.size() == 2 && sonobuoy.Operations.size() == 2);
	Require(sonobuoy.Operations[0].Invocation == Operation::Action::Use && sonobuoy.Operations[1].Invocation == Operation::Action::SetActive);
	Require(std::holds_alternative<Effect::Storage>(tank.Effects[0].Behavior));
	Require(std::get<double>(tankCapacity.Amount) == 0.3);
	Require(std::get<std::uint64_t>(helicopter.Loadouts[1].Equipment[3].InitialInventory[0].Amount) == 0);
	return 0;
}
