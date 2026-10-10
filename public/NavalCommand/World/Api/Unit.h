#pragma once
#include <NavalCommand/Orders/Api/Eligibility.h>
#include <NavalCommand/Orders/Api/Waypoint.h>
#include <NavalCommand/World/Api/Position.h>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::World::Api {
using Eligibility = NavalCommand::Orders::Api::Eligibility;
struct Unit {
	std::string id;
	std::string name;
	Position position;
	std::optional<double> speedMetersPerSecond;
	double sampledAtSeconds{};
	std::vector<Eligibility> orders;
	std::vector<Orders::Api::RoutePoint> plannedRoute;
	bool routeInspected{};
	std::optional<bool> airborne;
};
} // namespace NavalCommand::World::Api
