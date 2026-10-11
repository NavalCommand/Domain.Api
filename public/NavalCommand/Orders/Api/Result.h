#pragma once
#include <NavalCommand/Orders/Api/RouteMode.h>
#include <NavalCommand/Orders/Api/Stage.h>
#include <NavalCommand/Physics/Api/Meters.h>
#include <NavalCommand/Physics/Api/Seconds.h>
#include <NavalCommand/Units/Api/RoutePoint.h>
#include <NavalCommand/Units/Api/UnitId.h>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::Orders::Api
{
	struct Result
	{
		std::string SessionId;
		std::string RequestId;
		Orders::Api::Stage Stage{};
		std::string Reason;
		Physics::Api::Seconds SampledAt;
		std::optional<Physics::Api::Meters> Displacement;
		std::vector<Units::Api::RoutePoint> RouteBefore;
		std::vector<Units::Api::RoutePoint> RouteAfter;
		RouteMode Mode{};
		std::optional<Units::Api::UnitId> SpawnedUnit;
	};
}
