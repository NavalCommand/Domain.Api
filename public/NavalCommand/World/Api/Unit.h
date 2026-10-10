#pragma once
#include <NavalCommand/Orders/Api/Eligibility.h>
#include <NavalCommand/Orders/Api/RoutePoint.h>
#include <NavalCommand/World/Api/Position.h>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::World::Api
{
	struct Unit
	{
		std::string id;
		std::string name;
		Position position;
		std::optional<double> speedMetersPerSecond;
		double sampledAtSeconds{};
		std::vector<Orders::Api::Eligibility> orders;
		std::vector<Orders::Api::RoutePoint> plannedRoute;
		bool routeInspected{};
		std::optional<bool> airborne;
	};
}
