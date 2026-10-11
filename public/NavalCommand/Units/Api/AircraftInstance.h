#pragma once
#include <optional>

namespace NavalCommand::Units::Api
{
	struct AircraftInstance
	{
		std::optional<bool> Airborne;
	};
}
