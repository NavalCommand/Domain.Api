#pragma once
#include <NavalCommand/Catalog/Api/LoadoutId.h>
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <NavalCommand/Uncertainty/Api/Knowledge.h>
#include <cstdint>
#include <string>
#include <vector>

namespace NavalCommand::Units::Api
{
	struct AircraftInventoryEntry
	{
		Catalog::Api::UnitTypeId TypeId;
		std::string Squadron;
		Uncertainty::Api::Knowledge<std::uint32_t> UnreservedCount;
		// Available inventory definitions, not dynamically executable launch orders.
		std::vector<Catalog::Api::LoadoutId> Loadouts;
	};
}
