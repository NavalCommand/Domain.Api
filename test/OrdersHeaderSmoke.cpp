#include <NavalCommand/Orders/Api/OrderAvailability.h>
#include <NavalCommand/Orders/Api/Request.h>
#include <NavalCommand/Orders/Api/Result.h>
#include <type_traits>

namespace Orders = NavalCommand::Orders::Api;
namespace Units = NavalCommand::Units::Api;
namespace Uncertainty = NavalCommand::Uncertainty::Api;

static_assert(std::is_aggregate_v<Orders::Request>);
static_assert(std::is_aggregate_v<Orders::Result>);
static_assert(std::is_same_v<decltype(Orders::Request::Unit), Units::UnitId>);
static_assert(std::variant_size_v<decltype(Orders::Request::Payload)> == 2);
static_assert(static_cast<int>(Orders::Stage::MovementObserved) == 4);
static_assert(static_cast<int>(Orders::Availability::Unsupported) == 3);

int main()
{
	const Units::UnitId identity{"session-observation-1"};
	Orders::Request route{"session", "route", identity, 7, Orders::RouteCommand{{61.96}, {-10.37}, Orders::RouteMode::ReplaceRoute}};
	Orders::Request launch{"session", "launch", identity, 7, Orders::FacilityLaunch{{{"helicopter"}, "squadron", {"patrol"}}, 2}};
	Orders::OrderAvailability overlay;
	overlay.Unit = identity;
	overlay.BasedOnVersion = 7;
	using Discovery = Uncertainty::ObservedCollection<Orders::Eligibility>;
	overlay.Orders = {
		Discovery::Coverage::Complete,
		{{Orders::OrderKind::ReplaceRoute, Orders::Availability::Blocked, "native_automation_protected", std::nullopt},
		 {Orders::OrderKind::LaunchAircraft, Orders::Availability::Executable, "", std::get<Orders::FacilityLaunch>(launch.Payload)},
		 {Orders::OrderKind::AppendRoute, Orders::Availability::Unsupported, "unsupported_route_graph", std::nullopt},
		 {Orders::OrderKind::IdleWaypoint, Orders::Availability::Unknown, "state_unavailable", std::nullopt}}};
	Orders::Result receipt;
	receipt.Stage = Orders::Stage::AircraftSpawned;
	receipt.SpawnedUnit = Units::UnitId{"session-observation-2"};
	if (!std::holds_alternative<Orders::RouteCommand>(route.Payload) || !std::holds_alternative<Orders::FacilityLaunch>(launch.Payload))
	{
		return 1;
	}
	if (route.Unit != overlay.Unit || overlay.Orders.Items()[1].LaunchOption->Aircraft.Loadout.Value != "patrol")
	{
		return 1;
	}
	if (overlay.Orders.Items()[0].Availability != Orders::Availability::Blocked || receipt.Stage == Orders::Stage::Airborne)
	{
		return 1;
	}
	return receipt.SpawnedUnit->Value == "session-observation-2" ? 0 : 1;
}
