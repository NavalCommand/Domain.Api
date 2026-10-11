#pragma once
#include <NavalCommand/Observations/Api/ObservationId.h>
#include <NavalCommand/Observations/Api/ObserverId.h>
#include <NavalCommand/Orders/Api/LaunchAircraft.h>
#include <NavalCommand/Orders/Api/RouteCommand.h>
#include <cstdint>
#include <string>
#include <variant>

namespace NavalCommand::Orders::Api
{
	struct Request
	{
		std::string SessionId;
		std::string RequestId;
		Observations::Api::ObserverId Observer;
		Observations::Api::ObservationId Observation;
		std::uint64_t BasedOnVersion{};
		std::variant<RouteCommand, LaunchAircraft> Payload;
	};
}
