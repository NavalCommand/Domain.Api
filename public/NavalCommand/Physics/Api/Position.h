#pragma once
#include <NavalCommand/Physics/Api/Degrees.h>
#include <NavalCommand/Physics/Api/Meters.h>
#include <optional>

namespace NavalCommand::Physics::Api
{
	// Geodetic latitude/longitude in degrees; altitude above mean sea level in meters.
	struct Position
	{
		Degrees Latitude;
		Degrees Longitude;
		std::optional<Meters> Altitude;
	};
}
