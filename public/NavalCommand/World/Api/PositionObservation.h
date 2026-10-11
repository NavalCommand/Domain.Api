#pragma once
#include <NavalCommand/World/Api/Position.h>
#include <optional>

namespace NavalCommand::World::Api
{
	struct PositionObservation
	{
		struct Uncertainty
		{
			double MajorAxisMeters;
			double MinorAxisMeters;
			double OrientationRadians;
		};

		Position Coordinates;
		std::optional<Uncertainty> ErrorEllipse;
	};
}
