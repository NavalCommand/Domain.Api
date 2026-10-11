#pragma once
#include <optional>

namespace NavalCommand::Units::Api
{
	struct AircraftState
	{
		std::optional<bool> Airborne;
	};
}
