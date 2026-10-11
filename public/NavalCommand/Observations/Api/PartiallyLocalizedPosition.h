#pragma once
#include <NavalCommand/Observations/Api/ObservedErrorEllipse.h>
#include <NavalCommand/Physics/Api/Degrees.h>
#include <optional>

namespace NavalCommand::Observations::Api
{
	struct PartiallyLocalizedPosition
	{
		std::optional<Physics::Api::Degrees> Latitude;
		std::optional<Physics::Api::Degrees> Longitude;
		std::optional<Physics::Api::Meters> Elevation;
		std::optional<ObservedErrorEllipse> ErrorEllipse;
	};
}
