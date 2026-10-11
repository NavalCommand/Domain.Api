#pragma once
#include <NavalCommand/Catalog/Api/Loadout.h>
#include <NavalCommand/Catalog/Api/PlatformDescription.h>
#include <NavalCommand/Catalog/Api/UnitTypeId.h>
#include <vector>

namespace NavalCommand::Catalog::Api
{
	struct UnitType
	{
		UnitTypeId Id;
		PlatformDescription Platform;
		std::vector<Loadout> Loadouts;
	};
}
