#include <NavalCommand/Orders/Api/ExecutionRequest.h>
#include <NavalCommand/Orders/Api/LaunchAircraft.h>
#include <NavalCommand/Orders/Api/Route.h>
#include <NavalCommand/Units/Api/Id.h>
#include <gtest/gtest.h>
#include <type_traits>
#include <variant>

namespace Orders = NavalCommand::Orders::Api;
namespace Units = NavalCommand::Units::Api;

static_assert(std::variant_size_v<decltype(Orders::ExecutionRequest::Payload)> == 2);
static_assert(std::is_same_v<decltype(Orders::ExecutionRequest::Executor), Units::Id>);

TEST(ExecutionRequestTest, SupportsRouteAndAircraftPayloadsWithUnitExecutor)
{
	Orders::ExecutionRequest routeRequest;
	routeRequest.Executor = Units::Id{"unit-1"};
	routeRequest.Payload = Orders::RouteCommand{
		NavalCommand::Physics::Api::Position{{61.96}, {-10.37}, {0}},
		Orders::RouteCommand::RouteMode::ReplaceRoute};

	Orders::ExecutionRequest launchRequest;
	launchRequest.Executor = routeRequest.Executor;
	launchRequest.Payload = Orders::LaunchAircraft{{"helicopter"}, {"patrol"}, 2};

	EXPECT_EQ(routeRequest.Executor.Value, "unit-1");
	const auto& launch = std::get<Orders::LaunchAircraft>(launchRequest.Payload);
	EXPECT_EQ(launch.Count, 2);
	EXPECT_EQ(launch.AircraftType.Value, "helicopter");
}
