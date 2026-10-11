#pragma once
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <string>
#include <vector>

namespace NavalCommand::Observations::Api
{
	struct ObservedRoutePoint
	{
		Physics::Api::Position Position;
		std::string Label;
	};

	struct NavigationObservation
	{
		Uncertainty::Api::Knowledge<std::vector<ObservedRoutePoint>> PlannedRoute;
	};
}
