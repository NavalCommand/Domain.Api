#pragma once
#include <NavalCommand/Physics/Api/Position.h>
#include <string>

namespace NavalCommand::Operations::Api
{
	struct Waypoint
	{
		Physics::Api::Position TargetPosition;
		std::string Label;
	};
}
