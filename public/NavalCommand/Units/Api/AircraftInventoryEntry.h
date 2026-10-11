#pragma once
#include <../../Equipment/Api/LoadoutId.h>
#include <UnitTypeId.h>
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
