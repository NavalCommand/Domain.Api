#pragma once
#include <string>

namespace NavalCommand::Orders::Api
{
	enum class RouteMode
	{
		LegacyIdle,
		ReplaceRoute,
		AppendWaypoint
	};

	struct RoutePoint
	{
		double latitudeDeg{};
		double longitudeDeg{};
		std::string label;
	};

	struct Waypoint
	{
		double latitudeDeg{};
		double longitudeDeg{};
		RouteMode routeMode{};
	};
} // namespace NavalCommand::Orders::Api
