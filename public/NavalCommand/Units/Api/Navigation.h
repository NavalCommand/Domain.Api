#pragma once
#include <NavalCommand/Units/Api/Waypoint.h>
#include <vector>

namespace NavalCommand::Units::Api
{
	struct Navigation
	{
		std::vector<Waypoint> PlannedRoute;
	};
}
