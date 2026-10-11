#pragma once
#include <NavalCommand/Catalog/Api/LoadoutId.h>
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <string>

namespace NavalCommand::Units::Api
{
	// Identifies one aircraft/loadout choice in an owning unit's air-operations inventory.
	// A selection conveys no launch permission or current resource guarantee.
	struct AircraftSelection
	{
		Catalog::Api::UnitTypeId TypeId;
		std::string Squadron;
		Catalog::Api::LoadoutId Loadout;
	};
}
