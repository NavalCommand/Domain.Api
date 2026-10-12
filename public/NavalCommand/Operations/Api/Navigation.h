#pragma once
#include <NavalCommand/Operations/Api/Waypoint.h>
#include <vector>

namespace NavalCommand::Operations::Api
{
	struct Navigation
	{
		std::vector<Waypoint> PlannedRoute;
	};
}
