#include <NavalCommand/Orders/Api/Eligibility.h>
#include <NavalCommand/Orders/Api/Request.h>
#include <NavalCommand/Orders/Api/Result.h>
#include <NavalCommand/Orders/Api/RouteCommand.h>
#include <NavalCommand/Orders/Api/RoutePoint.h>
#include <NavalCommand/Orders/Api/Stage.h>
#include <type_traits>

namespace Orders = NavalCommand::Orders::Api;
static_assert(std::is_aggregate_v<Orders::Request>);
static_assert(std::is_aggregate_v<Orders::Result>);
static_assert(std::is_aggregate_v<Orders::RouteCommand>);
static_assert(std::is_aggregate_v<Orders::RoutePoint>);
static_assert(static_cast<int>(Orders::Stage::MovementObserved) == 4);
static_assert(static_cast<int>(Orders::Availability::Unsupported) == 3);

int main()
{
	Orders::Request request{"session", "request", "unit", 7, Orders::RouteCommand{61.96, -10.37}};
	Orders::Result result{"session", "request", Orders::Stage::NativeTaskCreated, "", 1.0, std::nullopt};
	Orders::Eligibility eligibility{"waypoint", Orders::Availability::Executable, "", "degrees"};
	Orders::RoutePoint routePoint{61.96, -10.37, "planned"};
	return request.routeCommand->latitudeDeg == 61.96 && !result.displacementMeters &&
		eligibility.availability == Orders::Availability::Executable && routePoint.label == "planned" ? 0 : 1;
}
