#pragma once
#include <NavalCommand/Orders/Api/RoutePoint.h>
#include <NavalCommand/World/Api/Knowledge.h>
#include <vector>

namespace NavalCommand::World::Api
{
	struct NavigationState
	{
		Knowledge<bool> Inspected;
		Knowledge<std::vector<Orders::Api::RoutePoint>> PlannedRoute;
	};
}
