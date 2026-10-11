#pragma once
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Uncertainty/Api/Exact.h>
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
		Uncertainty::Api::Exact<std::vector<ObservedRoutePoint>> PlannedRoute;
	};
}
