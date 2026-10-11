#pragma once
#include <NavalCommand/Observations/Api/AircraftSelection.h>
#include <cstdint>

namespace NavalCommand::Orders::Api
{
	struct LaunchAircraft
	{
		Observations::Api::AircraftSelection Aircraft;
		std::uint32_t Count{};
	};
}
