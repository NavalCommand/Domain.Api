#pragma once
#include <NavalCommand/Units/Api/AircraftSelection.h>
#include <cstdint>

namespace NavalCommand::Orders::Api
{
	struct FacilityLaunch
	{
		Units::Api::AircraftSelection Aircraft;
		std::uint32_t Count{};
	};
}
