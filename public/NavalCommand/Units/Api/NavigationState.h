#pragma once
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <NavalCommand/Units/Api/RoutePoint.h>
#include <vector>

namespace NavalCommand::Units::Api
{
	struct NavigationState
	{
		// Known(empty) is inspected and empty; Unknown means uninspected or unavailable.
		Uncertainty::Api::Knowledge<std::vector<RoutePoint>> PlannedRoute;
	};
}
