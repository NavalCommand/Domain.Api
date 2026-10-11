#pragma once
#include <NavalCommand/Orders/Api/FacilityLaunch.h>
#include <NavalCommand/Orders/Api/RouteCommand.h>
#include <NavalCommand/Units/Api/UnitId.h>
#include <cstdint>
#include <string>
#include <variant>

namespace NavalCommand::Orders::Api
{
	struct Request
	{
		std::string SessionId;
		std::string RequestId;
		Units::Api::UnitId Unit;
		std::uint64_t BasedOnVersion{};
		std::variant<RouteCommand, FacilityLaunch> Payload;
	};
}
