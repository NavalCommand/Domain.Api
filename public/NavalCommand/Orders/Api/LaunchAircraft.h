#pragma once
#include <cstdint>
#include <NavalCommand/Equipment/Api/LoadoutId.h>
#include <NavalCommand/Units/Api/TypeId.h>

namespace NavalCommand::Orders::Api
{
	struct LaunchAircraft
	{
		Units::Api::TypeId AircraftType;
		Equipment::Api::LoadoutId Loadout;
		std::uint32_t Count{};
	};
}
