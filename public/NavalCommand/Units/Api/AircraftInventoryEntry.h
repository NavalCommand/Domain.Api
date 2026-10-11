#pragma once
#include <NavalCommand/Catalog/Api/LoadoutId.h>
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <cstdint>
#include <optional>
#include <string>
#include <vector>

namespace NavalCommand::Units::Api
{
	struct AircraftInventoryEntry
	{
		Catalog::Api::UnitTypeId Type;
		std::string Squadron;
		std::optional<std::uint32_t> UnreservedCount;
		std::optional<std::vector<Catalog::Api::LoadoutId>> Loadouts;
	};
}
