#pragma once
#include <string>
#include <NavalCommand/Physics/Api/Position.h>

namespace NavalCommand::Units::Api
{
	struct Waypoint
	{
		Physics::Api::Position TargetPosition;
		std::string Label;
	};
}
