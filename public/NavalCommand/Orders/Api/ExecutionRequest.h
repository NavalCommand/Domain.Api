#pragma once
#include <NavalCommand/Orders/Api/LaunchAircraft.h>
#include <NavalCommand/Orders/Api/Route.h>
#include <NavalCommand/Units/Api/Id.h>
#include <cstdint>
#include <string>
#include <variant>

namespace NavalCommand::Orders::Api
{
	struct ExecutionRequest
	{
		Units::Api::Id Executor;
		std::variant<RouteCommand, LaunchAircraft> Payload;
	};
}
