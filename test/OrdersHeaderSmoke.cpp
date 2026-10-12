#include <NavalCommand/Equipment/Api/LoadoutId.h>
#include <NavalCommand/Orders/Api/Error.h>
#include <NavalCommand/Orders/Api/ExecutionRequest.h>
#include <NavalCommand/Orders/Api/ExecutionState.h>
#include <NavalCommand/Orders/Api/IProvider.h>
#include <NavalCommand/Orders/Api/Status.h>
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Units/Api/Id.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <type_traits>
#include <variant>

namespace Equipment = NavalCommand::Equipment::Api;
namespace Orders = NavalCommand::Orders::Api;
namespace Physics = NavalCommand::Physics::Api;
namespace Units = NavalCommand::Units::Api;

static_assert(std::is_abstract_v<Orders::IProvider>);
static_assert(std::variant_size_v<decltype(Orders::ExecutionRequest::Payload)> == 2);
static_assert(std::is_same_v<decltype(Orders::ExecutionRequest::Executor), Units::Id>);

int main()
{
	Orders::ExecutionRequest routeRequest;
	routeRequest.Executor = Units::Id{"unit-1"};
	routeRequest.Payload = Orders::RouteCommand{
		Physics::Position{{61.96}, {-10.37}, {0}},
		Orders::RouteCommand::RouteMode::ReplaceRoute};

	Orders::ExecutionRequest launchRequest;
	launchRequest.Executor = routeRequest.Executor;
	launchRequest.Payload = Orders::LaunchAircraft{{"helicopter"}, Equipment::LoadoutId{"patrol"}, 2};

	Orders::ExecutionState state;
	state.OrderId = {"order-7"};
	state.Request = routeRequest;
	state.OrderStatus = Orders::Status::Pending;

	const auto& launch = std::get<Orders::LaunchAircraft>(launchRequest.Payload);
	return launch.Count == 2 && launch.AircraftType.Value == "helicopter" &&
		std::holds_alternative<Orders::Status>(state.OrderStatus) &&
		state.OrderId.Value == "order-7" ? 0 : 1;
}
