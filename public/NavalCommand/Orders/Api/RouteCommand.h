#pragma once
#include <NavalCommand/Orders/Api/RouteMode.h>
#include <NavalCommand/Physics/Api/Degrees.h>

namespace NavalCommand::Orders::Api
{
	struct RouteCommand
	{
		Physics::Api::Degrees Latitude;
		Physics::Api::Degrees Longitude;
		RouteMode Mode{};
	};
}
