#pragma once
#include <NavalCommand/Orders/Api/FacilityLaunch.h>
#include <NavalCommand/Orders/Api/RouteCommand.h>
#include <cstdint>
#include <optional>
#include <string>

namespace NavalCommand::Orders::Api
{
	struct Request
	{
		std::string sessionId;
		std::string requestId;
		std::string entityId;
		std::uint64_t basedOnVersion{};
		std::optional<RouteCommand> routeCommand;
		std::optional<FacilityLaunch> facilityLaunch;
	};
}
