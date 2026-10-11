#pragma once
#include <NavalCommand/Physics/Api/Degrees.h>
#include <string>

namespace NavalCommand::Units::Api
{
	struct RoutePoint
	{
		Physics::Api::Degrees Latitude;
		Physics::Api::Degrees Longitude;
		std::string Label;
	};
}
