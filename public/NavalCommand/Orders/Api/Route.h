#pragma once
#include <NavalCommand/Orders/Api/RouteMode.h>

namespace NavalCommand::Orders::Api
{
	struct RouteCommand
	{
		enum class RouteMode
		{
			IdleWaypoint,
			ReplaceRoute,
			AppendWaypoint
		};

		Physics::Api::Position Waypoint;
		RouteMode Mode{};
	};
}
