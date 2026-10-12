#pragma once
#include <NavalCommand/Equipment/Api/LoadoutId.h>
#include <NavalCommand/Units/Api/TypeId.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::Operations::Api
{
	struct AircraftInventoryEntry
	{
		Units::Api::TypeId Type;
		std::string Squadron;
		std::optional<std::uint32_t> UnreservedCount;
		std::optional<std::vector<Equipment::Api::LoadoutId>> Loadouts;
	};
}
