#pragma once
#include <NavalCommand/Observations/Api/NavigationObservation.h>
#include <NavalCommand/Observations/Api/ObservationId.h>
#include <NavalCommand/Observations/Api/ObserverId.h>
#include <NavalCommand/Orders/Api/RouteMode.h>
#include <NavalCommand/Orders/Api/Stage.h>
#include <NavalCommand/Physics/Api/Meters.h>
#include <NavalCommand/Physics/Api/Seconds.h>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::Orders::Api
{
	struct Result
	{
		std::string SessionId;
		std::string RequestId;
		Observations::Api::ObserverId Observer;
		Orders::Api::Stage Stage{};
		std::string Reason;
		Physics::Api::Seconds SampledAt;
		std::optional<Physics::Api::Meters> Displacement;
		std::vector<Observations::Api::ObservedRoutePoint> RouteBefore;
		std::vector<Observations::Api::ObservedRoutePoint> RouteAfter;
		RouteMode Mode{};
		std::optional<Observations::Api::ObservationId> SpawnedObservation;
	};
}
