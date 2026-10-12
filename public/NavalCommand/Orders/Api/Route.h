#pragma once
#include <NavalCommand/Physics/Api/Position.h>

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
