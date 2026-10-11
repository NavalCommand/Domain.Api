#include <NavalCommand/Observations/Api/AircraftSelection.h>
#include <NavalCommand/Observations/Api/ObserverId.h>
#include <NavalCommand/Observations/Api/UnitObservation.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>
#include <cstdint>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

namespace Observations = NavalCommand::Observations::Api;
namespace Uncertainty = NavalCommand::Uncertainty::Api;
namespace Catalog = NavalCommand::Catalog::Api;
namespace Physics = NavalCommand::Physics::Api;

static_assert(!std::is_same_v<Observations::ObservationId, Observations::ObserverId>);
static_assert(std::is_same_v<decltype(Observations::UnitObservation::Identity), Observations::ObservationId>);
static_assert(std::is_same_v<decltype(Observations::UnitObservation::Type), Uncertainty::Exact<Catalog::UnitTypeId>>);
static_assert(std::is_same_v<decltype(Observations::UnitObservation::Name), Uncertainty::Exact<std::string>>);

int main()
{
	Observations::UnitObservation falseContact;
	falseContact.Identity = {"observer-a-contact-9"};
	falseContact.Name = Uncertainty::Exact<std::string>::Unknown();
	falseContact.Type = Uncertainty::Exact<Catalog::UnitTypeId>::Unknown();
	falseContact.Kinematics.Position = Observations::PartiallyLocalizedPosition{
		Physics::Degrees{61.9}, Physics::Degrees{-10.3},
		Observations::ObservedErrorEllipse{Physics::Meters{1200}, Physics::Meters{650}, Physics::Radians{0.25}}};
	falseContact.Contributors.push_back({{"ally-contact-2"}, {{"surface-search-radar"}}});
	const auto& partialPosition = std::get<Observations::PartiallyLocalizedPosition>(falseContact.Kinematics.Position);

	Observations::UnitObservation ownObservation;
	ownObservation.Identity = {"observer-a-own-unit"};
	ownObservation.Name = Uncertainty::Exact<std::string>::Known("HMS Example");
	ownObservation.MeasuredAt = Uncertainty::Exact<Physics::Seconds>::Known({5});
	ownObservation.Kinematics.Position = Uncertainty::Exact<Physics::Position>::Known(
		{{61.9}, {-10.3}, Physics::Meters{0}});

	const Observations::UnitObservation unknownPosition;
	Observations::UnitObservation fused = falseContact;
	fused.Identity = {"observer-a-fused-contact"};
	fused.Name = Uncertainty::Exact<std::string>::Unknown();
	fused.Contributors.clear(); // An aggregate contact may have no supported individual attribution.

	Observations::AirOperationsObservation airOperations;
	airOperations.Inventory.push_back({
		Uncertainty::Exact<Catalog::UnitTypeId>::Known({"helicopter"}),
		Uncertainty::Exact<std::string>::Known("squadron-a"),
		Uncertainty::Exact<std::uint32_t>::Known(4),
		{{"strike"}, {"patrol"}}});
	falseContact.AirOperations = airOperations;
	const Observations::AircraftSelection launchSelection{{"helicopter"}, "squadron-a", {"patrol"}};
	const auto& stock = falseContact.AirOperations->Inventory[0];

	Observations::NavigationObservation navigation;
	navigation.PlannedRoute = Uncertainty::Exact<std::vector<Observations::ObservedRoutePoint>>::Known({});
	return falseContact.Identity.Value != fused.Identity.Value &&
		!falseContact.Name.HasValue() && ownObservation.Name.IsKnown() &&
		!falseContact.MeasuredAt.HasValue() && ownObservation.MeasuredAt.Value().Value == 5 &&
		!falseContact.Type.IsKnown() &&
		partialPosition.ErrorEllipse->MajorAxis.Value == 1200 &&
		partialPosition.ErrorEllipse->MinorAxis.Value == 650 &&
		partialPosition.ErrorEllipse->Orientation.Value == 0.25 &&
		std::get<Uncertainty::Exact<Physics::Position>>(ownObservation.Kinematics.Position).IsKnown() &&
		!std::get<Uncertainty::Exact<Physics::Position>>(unknownPosition.Kinematics.Position).HasValue() &&
		falseContact.Contributors.size() == 1 && fused.Contributors.empty() &&
		stock.UnreservedCount.Value() == 4 && stock.Loadouts.size() == 2 &&
		launchSelection.Loadout.Value == stock.Loadouts[1].Value &&
		navigation.PlannedRoute.IsKnown() && navigation.PlannedRoute.Value().empty() ? 0 : 1;
}
