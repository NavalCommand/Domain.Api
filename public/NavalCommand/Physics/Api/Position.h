#pragma once
#include <NavalCommand/Physics/Api/Degrees.h>
#include <NavalCommand/Physics/Api/Meters.h>
#include <optional>

namespace NavalCommand::Physics::Api
{
	struct Position
	{
		Degrees Latitude;
		Degrees Longitude;
		Meters Elevation;
	};
}
