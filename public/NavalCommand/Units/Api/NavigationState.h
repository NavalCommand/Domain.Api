#pragma once
#include <NavalCommand/Units/Api/RoutePoint.h>
#include <vector>

namespace NavalCommand::Units::Api
{
	struct NavigationState
	{
		std::vector<RoutePoint> PlannedRoute;
	};
}
