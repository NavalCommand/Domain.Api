#include <NavalCommand/Orders/Api/OrderAvailability.h>
#include <NavalCommand/Orders/Api/Request.h>
#include <NavalCommand/Orders/Api/Result.h>
#include <type_traits>

namespace Orders = NavalCommand::Orders::Api;
namespace Observations = NavalCommand::Observations::Api;
namespace Catalog = NavalCommand::Catalog::Api;
namespace Uncertainty = NavalCommand::Uncertainty::Api;
namespace Physics = NavalCommand::Physics::Api;

static_assert(std::is_aggregate_v<Orders::Request>);
static_assert(std::is_aggregate_v<Orders::Result>);
static_assert(std::is_same_v<decltype(Orders::Request::Observation), Observations::ObservationId>);

int main()
{
	Orders::Request request{"session", "request", {"observer-a"}, {"contact-a"}, 7,
		Orders::RouteCommand{{61.96}, {-10.37}, Orders::RouteMode::ReplaceRoute}};
	Orders::Request launch{"session", "launch", request.Observer, request.Observation, 7,
		Orders::LaunchAircraft{{Catalog::UnitTypeId{"helicopter"}, "squadron-a", Catalog::LoadoutId{"patrol"}}, 1}};
	Orders::OrderAvailability overlay;
	overlay.Observer = request.Observer;
	overlay.Observation = request.Observation;
	overlay.BasedOnVersion = request.BasedOnVersion;
	using Discovery = Uncertainty::ObservedCollection<Orders::Eligibility>;
	overlay.Orders = {Discovery::Coverage::Complete,
		{{Orders::OrderKind::ReplaceRoute, Orders::Availability::Executable, "", std::nullopt},
		 {Orders::OrderKind::LaunchAircraft, Orders::Availability::Executable, "", std::get<Orders::LaunchAircraft>(launch.Payload)}}};
	Orders::Result result;
	result.Observer = request.Observer;
	result.SpawnedObservation = Observations::ObservationId{"contact-spawned"};
	result.RouteBefore.push_back({{{61.96}, {-10.37}, std::nullopt}, "harbor"});
	result.RouteAfter.push_back({{{62.0}, {-10.3}, std::nullopt}, "waypoint"});
	return overlay.Observation == request.Observation && overlay.Orders.Items().size() == 2 &&
		std::holds_alternative<Orders::LaunchAircraft>(launch.Payload) &&
		result.SpawnedObservation.has_value() && result.RouteAfter[0].Label == "waypoint" ? 0 : 1;
}
