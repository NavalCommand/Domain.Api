#pragma once
#include <NavalCommand/Physics/Api/Position.h>
#include <NavalCommand/Physics/Api/Radians.h>
#include <optional>

namespace NavalCommand::Units::Api
{
	struct PositionObservation
	{
		struct Uncertainty
		{
			Physics::Api::Meters MajorAxis;
			Physics::Api::Meters MinorAxis;
			// Clockwise orientation from geodetic north, in radians.
			Physics::Api::Radians Orientation;
		};

		Physics::Api::Position Coordinates;
		std::optional<Uncertainty> ErrorEllipse;
	};
}
